/**
 * The `contract` module provides utilities for deploying and interacting with contracts, based on a
 * `Wallet` instance and a compiled artifact. Refer to the {@link account} module for how to obtain a valid
 * `Wallet` instance, and to the {@link https://docs.aztec.network/developers/contracts/compiling | Compiling contracts}
 * section of the documentation for how to generate an artifact out of your Noir source code.
 *
 * The {@link Contract} class is the main class in this module, and provides static methods for deploying
 * a contract or interacting with an already deployed one. The `methods` property of the contract instance
 * provides access to private, public, and simulate methods, that can be invoked in a transaction via `send()`,
 * or can be queried via `simulate()`.
 *
 * ```ts
 * const contract = await Contract.deploy(wallet, MyContractArtifact, [...constructorArgs]).send().deployed();
 * console.log(`Contract deployed at ${contract.address}`);
 * ```
 *
 * ```ts
 * const contract = await Contract.at(address, MyContractArtifact, wallet);
 * await contract.methods.mint(1000, owner).send().wait();
 * console.log(`Total supply is now ${await contract.methods.totalSupply().simulate()}`);
 * ```
 *
 * The result of calling a method in a contract instance, such as `contract.methods.mint(1000, owner)`
 * in the example, is a {@link ContractFunctionInteraction} instance. Usually this will be just sent as
 * a transaction to the network via the `send` method, but you can also `simulate` it without sending,
 * or obtaining the `request` for aggregating into a {@link BatchCall}.
 *
 * The result of `send`ing a transaction is a {@link SentTx} object, from which you can get the
 * transaction hash, or simply `wait` until the transaction is mined and the local PXE Service
 * has synchronized its changes.
 *
 * @remarks If you are using typescript, consider using the
 * {@link https://docs.aztec.network/developers/contracts/compiling#typescript-interfaces | autogenerated type-safe interfaces}
 * for interacting with your contracts.
 *
 * @packageDocumentation
 */
export { Contract } from './contract.js';
export {
  ContractFunctionInteraction,
  type ProfileResult,
  type SendMethodOptions,
} from './contract_function_interaction.js';
export { DefaultWaitOpts, SentTx, type WaitOpts } from './sent_tx.js';
export { ContractBase, type ContractMethod, type ContractNotes, type ContractStorageLayout } from './contract_base.js';
export { BatchCall } from './batch_call.js';
export { type DeployOptions, DeployMethod } from './deploy_method.js';
export { DeploySentTx } from './deploy_sent_tx.js';
