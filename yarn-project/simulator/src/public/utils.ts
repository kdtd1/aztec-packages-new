import { type PublicExecutionRequest, type Tx, TxExecutionPhase } from '@aztec/circuit-types';
import {
  type AvmCircuitPublicInputs,
  type Fr,
  type Gas,
  type GasSettings,
  type GlobalVariables,
  MAX_L2_TO_L1_MSGS_PER_TX,
  MAX_NOTE_HASHES_PER_TX,
  MAX_NULLIFIERS_PER_TX,
  MAX_PUBLIC_DATA_UPDATE_REQUESTS_PER_TX,
  PrivateToAvmAccumulatedData,
  PrivateToAvmAccumulatedDataArrayLengths,
  type PrivateToPublicAccumulatedData,
  PublicAccumulatedData,
  PublicCallRequest,
  PublicDataWrite,
  type RevertCode,
  type StateReference,
  TreeSnapshots,
  countAccumulatedItems,
  mergeAccumulatedData,
} from '@aztec/circuits.js';
import { computeNoteHashNonce, computeUniqueNoteHash, siloNoteHash } from '@aztec/circuits.js/hash';
import { padArrayEnd } from '@aztec/foundation/collection';
import { assertLength } from '@aztec/foundation/serialize';

import { type PublicEnqueuedCallSideEffectTrace } from './enqueued_call_side_effect_trace.js';

export function getExecutionRequestsByPhase(tx: Tx, phase: TxExecutionPhase): PublicExecutionRequest[] {
  switch (phase) {
    case TxExecutionPhase.SETUP:
      return tx.getNonRevertiblePublicExecutionRequests();
    case TxExecutionPhase.APP_LOGIC:
      return tx.getRevertiblePublicExecutionRequests();
    case TxExecutionPhase.TEARDOWN: {
      const request = tx.getPublicTeardownExecutionRequest();
      return request ? [request] : [];
    }
    default:
      throw new Error(`Unknown phase: ${phase}`);
  }
}

export function getCallRequestsByPhase(tx: Tx, phase: TxExecutionPhase): PublicCallRequest[] {
  switch (phase) {
    case TxExecutionPhase.SETUP:
      return tx.data.getNonRevertiblePublicCallRequests();
    case TxExecutionPhase.APP_LOGIC:
      return tx.data.getRevertiblePublicCallRequests();
    case TxExecutionPhase.TEARDOWN: {
      const request = tx.data.getTeardownPublicCallRequest();
      return request ? [request] : [];
    }
    default:
      throw new Error(`Unknown phase: ${phase}`);
  }
}

export function convertPrivateToPublicAccumulatedData(
  fromPrivate: PrivateToPublicAccumulatedData,
): PublicAccumulatedData {
  const to = PublicAccumulatedData.empty();
  to.noteHashes.forEach((_, i) => (to.noteHashes[i].noteHash.value = fromPrivate.noteHashes[i]));
  to.nullifiers.forEach((_, i) => (to.nullifiers[i].value = fromPrivate.nullifiers[i]));
  to.l2ToL1Msgs.forEach((_, i) => (to.l2ToL1Msgs[i] = fromPrivate.l2ToL1Msgs[i]));
  to.noteEncryptedLogsHashes.forEach(
    (_, i) => (to.noteEncryptedLogsHashes[i] = fromPrivate.noteEncryptedLogsHashes[i]),
  );
  to.encryptedLogsHashes.forEach((_, i) => (to.encryptedLogsHashes[i] = fromPrivate.encryptedLogsHashes[i]));
  to.publicCallStack.forEach((_, i) => (to.publicCallStack[i] = fromPrivate.publicCallRequests[i]));
  return to;
}

export function generateAvmCircuitPublicInputs(
  trace: PublicEnqueuedCallSideEffectTrace,
  globalVariables: GlobalVariables,
  startStateReference: StateReference,
  startGasUsed: Gas,
  gasSettings: GasSettings,
  setupCallRequests: PublicCallRequest[],
  appLogicCallRequests: PublicCallRequest[],
  teardownCallRequests: PublicCallRequest[],
  nonRevertibleAccumulatedDataFromPrivate: PrivateToPublicAccumulatedData,
  revertibleAccumulatedDataFromPrivate: PrivateToPublicAccumulatedData,
  endStateReference: StateReference,
  endGasUsed: Gas,
  transactionFee: Fr,
  revertCode: RevertCode,
): AvmCircuitPublicInputs {
  const startTreeSnapshots = new TreeSnapshots(
    startStateReference.l1ToL2MessageTree,
    startStateReference.partial.noteHashTree,
    startStateReference.partial.nullifierTree,
    startStateReference.partial.publicDataTree,
  );
  const endTreeSnapshots = new TreeSnapshots(
    endStateReference.l1ToL2MessageTree,
    endStateReference.partial.noteHashTree,
    endStateReference.partial.nullifierTree,
    endStateReference.partial.publicDataTree,
  );

  const avmCircuitPublicInputs = trace.toAvmCircuitPublicInputs(
    globalVariables,
    startTreeSnapshots,
    startGasUsed,
    gasSettings,
    setupCallRequests,
    appLogicCallRequests,
    teardownCallRequests.length ? teardownCallRequests[0] : PublicCallRequest.empty(),
    endTreeSnapshots,
    endGasUsed,
    transactionFee,
    !revertCode.isOK(),
  );

  const getArrayLengths = (from: PrivateToPublicAccumulatedData) =>
    new PrivateToAvmAccumulatedDataArrayLengths(
      countAccumulatedItems(from.noteHashes),
      countAccumulatedItems(from.nullifiers),
      countAccumulatedItems(from.l2ToL1Msgs),
    );
  const convertAccumulatedData = (from: PrivateToPublicAccumulatedData) =>
    new PrivateToAvmAccumulatedData(from.noteHashes, from.nullifiers, from.l2ToL1Msgs);
  // Temporary overrides as these entries aren't yet populated in trace
  avmCircuitPublicInputs.previousNonRevertibleAccumulatedDataArrayLengths = getArrayLengths(
    nonRevertibleAccumulatedDataFromPrivate,
  );
  avmCircuitPublicInputs.previousRevertibleAccumulatedDataArrayLengths = getArrayLengths(
    revertibleAccumulatedDataFromPrivate,
  );
  avmCircuitPublicInputs.previousNonRevertibleAccumulatedData = convertAccumulatedData(
    nonRevertibleAccumulatedDataFromPrivate,
  );
  avmCircuitPublicInputs.previousRevertibleAccumulatedData = convertAccumulatedData(
    revertibleAccumulatedDataFromPrivate,
  );

  // merge all revertible & non-revertible side effects into output accumulated data
  const noteHashesFromPrivate = revertCode.isOK()
    ? mergeAccumulatedData(
        avmCircuitPublicInputs.previousNonRevertibleAccumulatedData.noteHashes,
        avmCircuitPublicInputs.previousRevertibleAccumulatedData.noteHashes,
      )
    : avmCircuitPublicInputs.previousNonRevertibleAccumulatedData.noteHashes;
  avmCircuitPublicInputs.accumulatedData.noteHashes = assertLength(
    mergeAccumulatedData(noteHashesFromPrivate, avmCircuitPublicInputs.accumulatedData.noteHashes),
    MAX_NOTE_HASHES_PER_TX,
  );

  const txHash = avmCircuitPublicInputs.previousNonRevertibleAccumulatedData.nullifiers[0];

  const scopedNoteHashesFromPublic = trace.getSideEffects().noteHashes;
  for (let i = 0; i < scopedNoteHashesFromPublic.length; i++) {
    const scopedNoteHash = scopedNoteHashesFromPublic[i];
    const noteHash = scopedNoteHash.value;
    if (!noteHash.isZero()) {
      const noteHashIndexInTx = i + countAccumulatedItems(noteHashesFromPrivate);
      const nonce = computeNoteHashNonce(txHash, noteHashIndexInTx);
      const uniqueNoteHash = computeUniqueNoteHash(nonce, noteHash);
      const siloedNoteHash = siloNoteHash(scopedNoteHash.contractAddress, uniqueNoteHash);
      avmCircuitPublicInputs.accumulatedData.noteHashes[noteHashIndexInTx] = siloedNoteHash;
    }
  }

  const nullifiersFromPrivate = revertCode.isOK()
    ? mergeAccumulatedData(
        avmCircuitPublicInputs.previousNonRevertibleAccumulatedData.nullifiers,
        avmCircuitPublicInputs.previousRevertibleAccumulatedData.nullifiers,
      )
    : avmCircuitPublicInputs.previousNonRevertibleAccumulatedData.nullifiers;
  avmCircuitPublicInputs.accumulatedData.nullifiers = assertLength(
    mergeAccumulatedData(nullifiersFromPrivate, avmCircuitPublicInputs.accumulatedData.nullifiers),
    MAX_NULLIFIERS_PER_TX,
  );
  const msgsFromPrivate = revertCode.isOK()
    ? mergeAccumulatedData(
        avmCircuitPublicInputs.previousNonRevertibleAccumulatedData.l2ToL1Msgs,
        avmCircuitPublicInputs.previousRevertibleAccumulatedData.l2ToL1Msgs,
      )
    : avmCircuitPublicInputs.previousNonRevertibleAccumulatedData.l2ToL1Msgs;
  avmCircuitPublicInputs.accumulatedData.l2ToL1Msgs = assertLength(
    mergeAccumulatedData(msgsFromPrivate, avmCircuitPublicInputs.accumulatedData.l2ToL1Msgs),
    MAX_L2_TO_L1_MSGS_PER_TX,
  );

  const dedupedPublicDataWrites: Array<PublicDataWrite> = [];
  const leafSlotOccurences: Map<bigint, number> = new Map();
  for (const publicDataWrite of avmCircuitPublicInputs.accumulatedData.publicDataWrites) {
    const slot = publicDataWrite.leafSlot.toBigInt();
    const prevOccurrences = leafSlotOccurences.get(slot) || 0;
    leafSlotOccurences.set(slot, prevOccurrences + 1);
  }

  for (const publicDataWrite of avmCircuitPublicInputs.accumulatedData.publicDataWrites) {
    const slot = publicDataWrite.leafSlot.toBigInt();
    const prevOccurrences = leafSlotOccurences.get(slot) || 0;
    if (prevOccurrences === 1) {
      dedupedPublicDataWrites.push(publicDataWrite);
    } else {
      leafSlotOccurences.set(slot, prevOccurrences - 1);
    }
  }

  avmCircuitPublicInputs.accumulatedData.publicDataWrites = padArrayEnd(
    dedupedPublicDataWrites,
    PublicDataWrite.empty(),
    MAX_PUBLIC_DATA_UPDATE_REQUESTS_PER_TX,
  );
  //console.log(`AvmCircuitPublicInputs:\n${inspect(avmCircuitPublicInputs)}`);
  return avmCircuitPublicInputs;
}
