import { type PublicExecutionRequest } from '@aztec/circuit-types';
import { type AvmSimulationStats } from '@aztec/circuit-types/stats';
import {
  type CombinedConstantData,
  Fr,
  Gas,
  type GlobalVariables,
  type Nullifier,
  PublicAccumulatedDataArrayLengths,
  PublicValidationRequestArrayLengths,
  type TxContext,
} from '@aztec/circuits.js';
import { createDebugLogger } from '@aztec/foundation/log';
import { Timer } from '@aztec/foundation/timer';
import { type TelemetryClient } from '@aztec/telemetry-client';

import { AvmContext } from '../avm/avm_context.js';
import { AvmExecutionEnvironment } from '../avm/avm_execution_environment.js';
import { AvmMachineState } from '../avm/avm_machine_state.js';
import { AvmSimulator } from '../avm/avm_simulator.js';
import { AvmPersistableStateManager } from '../avm/journal/index.js';
import { getPublicFunctionDebugName } from '../common/debug_fn_name.js';
import { DualSideEffectTrace } from './dual_side_effect_trace.js';
import { PublicEnqueuedCallSideEffectTrace } from './enqueued_call_side_effect_trace.js';
import { type PublicExecutionResult } from './execution.js';
import { ExecutorMetrics } from './executor_metrics.js';
import { type WorldStateDB } from './public_db_sources.js';
import { PublicSideEffectTrace } from './side_effect_trace.js';

/**
 * Handles execution of public functions.
 */
export class PublicExecutor {
  metrics: ExecutorMetrics;

  constructor(private readonly worldStateDB: WorldStateDB, client: TelemetryClient) {
    this.metrics = new ExecutorMetrics(client, 'PublicExecutor');
  }

  static readonly log = createDebugLogger('aztec:simulator:public_executor');

  /**
   * Executes a public execution request.
   * @param executionRequest - The execution to run.
   * @param constants - The constants (including global variables) to use.
   * @param allocatedGas - The gas available at the start of this enqueued call.
   * @param txContext - Transaction context.
   * @param pendingSiloedNullifiers - The pending nullifier set from earlier parts of this TX.
   * @param transactionFee - Fee offered for this TX.
   * @param startSideEffectCounter - The counter of the first side-effect generated by this simulation.
   * @param previousValidationRequestArrayLengths - Side effect array lengths from previous kernel
   * @param previousAccumulatedDataArrayLengths - Side effect array lengths from previous kernel
   * @returns The result of execution, including the results of all nested calls.
   */
  public async simulate(
    executionRequest: PublicExecutionRequest,
    constants: CombinedConstantData,
    allocatedGas: Gas,
    _txContext: TxContext,
    pendingSiloedNullifiers: Nullifier[],
    transactionFee: Fr = Fr.ZERO,
    startSideEffectCounter: number = 0,
    previousValidationRequestArrayLengths: PublicValidationRequestArrayLengths = PublicValidationRequestArrayLengths.empty(),
    previousAccumulatedDataArrayLengths: PublicAccumulatedDataArrayLengths = PublicAccumulatedDataArrayLengths.empty(),
  ): Promise<PublicExecutionResult> {
    const address = executionRequest.callContext.contractAddress;
    const selector = executionRequest.callContext.functionSelector;
    const fnName = await getPublicFunctionDebugName(this.worldStateDB, address, selector, executionRequest.args);

    PublicExecutor.log.verbose(
      `[AVM] Executing public external function ${fnName}@${address} with ${allocatedGas.l2Gas} allocated L2 gas.`,
    );
    const timer = new Timer();

    const innerCallTrace = new PublicSideEffectTrace(startSideEffectCounter);
    const enqueuedCallTrace = new PublicEnqueuedCallSideEffectTrace(
      startSideEffectCounter,
      previousValidationRequestArrayLengths,
      previousAccumulatedDataArrayLengths,
    );
    const trace = new DualSideEffectTrace(innerCallTrace, enqueuedCallTrace);
    const avmPersistableState = AvmPersistableStateManager.newWithPendingSiloedNullifiers(
      this.worldStateDB,
      trace,
      pendingSiloedNullifiers.map(n => n.value),
    );

    const avmExecutionEnv = createAvmExecutionEnvironment(executionRequest, constants.globalVariables, transactionFee);

    const avmMachineState = new AvmMachineState(allocatedGas);
    const avmContext = new AvmContext(avmPersistableState, avmExecutionEnv, avmMachineState);
    const simulator = new AvmSimulator(avmContext);
    const avmResult = await simulator.execute();
    const bytecode = simulator.getBytecode()!;

    // Commit the public storage state to the DBs since this is a top-level execution.
    // Observe that this will write all the state changes to the DBs, not only the latest for each slot.
    // However, the underlying DB keep a cache and will only write the latest state to disk.
    // TODO(dbanks12): this should be unnecessary here or should be exposed by state manager
    await avmContext.persistableState.publicStorage.commitToDB();

    PublicExecutor.log.verbose(
      `[AVM] ${fnName} returned, reverted: ${avmResult.reverted}${
        avmResult.reverted ? ', reason: ' + avmResult.revertReason : ''
      }.`,
      {
        eventName: 'avm-simulation',
        appCircuitName: fnName,
        duration: timer.ms(),
        bytecodeSize: bytecode!.length,
      } satisfies AvmSimulationStats,
    );

    const publicExecutionResult = trace.toPublicExecutionResult(
      avmExecutionEnv,
      /*startGasLeft=*/ allocatedGas,
      /*endGasLeft=*/ Gas.from(avmContext.machineState.gasLeft),
      bytecode,
      avmResult,
      fnName,
    );

    if (publicExecutionResult.reverted) {
      this.metrics.recordFunctionSimulationFailure();
    } else {
      this.metrics.recordFunctionSimulation(bytecode.length, timer.ms());
    }

    const _vmCircuitPublicInputs = enqueuedCallTrace.toVMCircuitPublicInputs(
      constants,
      avmExecutionEnv,
      /*startGasLeft=*/ allocatedGas,
      /*endGasLeft=*/ Gas.from(avmContext.machineState.gasLeft),
      avmResult,
    );

    PublicExecutor.log.verbose(
      `[AVM] ${fnName} simulation complete. Reverted=${avmResult.reverted}. Consumed ${
        allocatedGas.l2Gas - avmContext.machineState.gasLeft.l2Gas
      } L2 gas, ending with ${avmContext.machineState.gasLeft.l2Gas} L2 gas left.`,
    );

    return publicExecutionResult;
  }
}

/**
 * Convert a PublicExecutionRequest object to an AvmExecutionEnvironment
 *
 * @param executionRequest
 * @param globalVariables
 * @returns
 */
function createAvmExecutionEnvironment(
  executionRequest: PublicExecutionRequest,
  globalVariables: GlobalVariables,
  transactionFee: Fr,
): AvmExecutionEnvironment {
  return new AvmExecutionEnvironment(
    executionRequest.callContext.contractAddress,
    executionRequest.callContext.msgSender,
    executionRequest.callContext.functionSelector,
    /*contractCallDepth=*/ Fr.zero(),
    transactionFee,
    globalVariables,
    executionRequest.callContext.isStaticCall,
    executionRequest.args,
  );
}
