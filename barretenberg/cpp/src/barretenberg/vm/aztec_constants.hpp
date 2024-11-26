// GENERATED FILE - DO NOT EDIT, RUN yarn remake-constants in circuits.js
#pragma once

#define MAX_NOTE_HASHES_PER_CALL 16
#define MAX_NULLIFIERS_PER_CALL 16
#define MAX_ENQUEUED_CALLS_PER_CALL 16
#define MAX_L2_TO_L1_MSGS_PER_CALL 2
#define MAX_PUBLIC_DATA_UPDATE_REQUESTS_PER_CALL 64
#define MAX_PUBLIC_DATA_READS_PER_CALL 64
#define MAX_NOTE_HASH_READ_REQUESTS_PER_CALL 16
#define MAX_NULLIFIER_READ_REQUESTS_PER_CALL 16
#define MAX_NULLIFIER_NON_EXISTENT_READ_REQUESTS_PER_CALL 16
#define MAX_L1_TO_L2_MSG_READ_REQUESTS_PER_CALL 16
#define MAX_UNENCRYPTED_LOGS_PER_CALL 4
#define MAX_NOTE_HASHES_PER_TX 64
#define MAX_NULLIFIERS_PER_TX 64
#define MAX_ENQUEUED_CALLS_PER_TX 32
#define MAX_PUBLIC_DATA_UPDATE_REQUESTS_PER_TX 63
#define MAX_L2_TO_L1_MSGS_PER_TX 8
#define MAX_UNENCRYPTED_LOGS_PER_TX 8
#define MAX_PACKED_PUBLIC_BYTECODE_SIZE_IN_FIELDS 3000
#define MAX_L2_GAS_PER_ENQUEUED_CALL 12000000
#define AZTEC_ADDRESS_LENGTH 1
#define GAS_FEES_LENGTH 2
#define GAS_LENGTH 2
#define CALL_CONTEXT_LENGTH 4
#define CONTENT_COMMITMENT_LENGTH 4
#define CONTRACT_STORAGE_READ_LENGTH 3
#define CONTRACT_STORAGE_UPDATE_REQUEST_LENGTH 3
#define GLOBAL_VARIABLES_LENGTH 9
#define APPEND_ONLY_TREE_SNAPSHOT_LENGTH 2
#define L2_TO_L1_MESSAGE_LENGTH 3
#define PARTIAL_STATE_REFERENCE_LENGTH 6
#define READ_REQUEST_LENGTH 2
#define LOG_HASH_LENGTH 3
#define NOTE_HASH_LENGTH 2
#define NULLIFIER_LENGTH 3
#define PUBLIC_INNER_CALL_REQUEST_LENGTH 13
#define STATE_REFERENCE_LENGTH 8
#define TOTAL_FEES_LENGTH 1
#define HEADER_LENGTH 24
#define PUBLIC_CIRCUIT_PUBLIC_INPUTS_LENGTH 866
#define AVM_ACCUMULATED_DATA_LENGTH 318
#define AVM_CIRCUIT_PUBLIC_INPUTS_LENGTH 1006
#define AVM_VERIFICATION_KEY_LENGTH_IN_FIELDS 86
#define AVM_PROOF_LENGTH_IN_FIELDS 4166
#define AVM_PUBLIC_COLUMN_MAX_SIZE 1024
#define AVM_PUBLIC_INPUTS_FLATTENED_SIZE 2914
#define MEM_TAG_FF 0
#define MEM_TAG_U1 1
#define MEM_TAG_U8 2
#define MEM_TAG_U16 3
#define MEM_TAG_U32 4
#define MEM_TAG_U64 5
#define MEM_TAG_U128 6
#define SENDER_KERNEL_INPUTS_COL_OFFSET 0
#define ADDRESS_KERNEL_INPUTS_COL_OFFSET 1
#define FUNCTION_SELECTOR_KERNEL_INPUTS_COL_OFFSET 2
#define IS_STATIC_CALL_KERNEL_INPUTS_COL_OFFSET 3
#define CHAIN_ID_KERNEL_INPUTS_COL_OFFSET 4
#define VERSION_KERNEL_INPUTS_COL_OFFSET 5
#define BLOCK_NUMBER_KERNEL_INPUTS_COL_OFFSET 6
#define TIMESTAMP_KERNEL_INPUTS_COL_OFFSET 7
#define FEE_PER_DA_GAS_KERNEL_INPUTS_COL_OFFSET 8
#define FEE_PER_L2_GAS_KERNEL_INPUTS_COL_OFFSET 9
#define DA_START_GAS_KERNEL_INPUTS_COL_OFFSET 10
#define L2_START_GAS_KERNEL_INPUTS_COL_OFFSET 11
#define DA_END_GAS_KERNEL_INPUTS_COL_OFFSET 12
#define L2_END_GAS_KERNEL_INPUTS_COL_OFFSET 13
#define TRANSACTION_FEE_KERNEL_INPUTS_COL_OFFSET 14
#define START_NOTE_HASH_EXISTS_WRITE_OFFSET 0
#define START_NULLIFIER_EXISTS_OFFSET 16
#define START_NULLIFIER_NON_EXISTS_OFFSET 32
#define START_L1_TO_L2_MSG_EXISTS_WRITE_OFFSET 48
#define START_SSTORE_WRITE_OFFSET 64
#define START_SLOAD_WRITE_OFFSET 128
#define START_EMIT_NOTE_HASH_WRITE_OFFSET 192
#define START_EMIT_NULLIFIER_WRITE_OFFSET 208
#define START_EMIT_L2_TO_L1_MSG_WRITE_OFFSET 224
#define START_EMIT_UNENCRYPTED_LOG_WRITE_OFFSET 226
#define AVM_ADD_BASE_L2_GAS 32
#define AVM_SUB_BASE_L2_GAS 32
#define AVM_MUL_BASE_L2_GAS 33
#define AVM_DIV_BASE_L2_GAS 43
#define AVM_FDIV_BASE_L2_GAS 32
#define AVM_EQ_BASE_L2_GAS 32
#define AVM_LT_BASE_L2_GAS 64
#define AVM_LTE_BASE_L2_GAS 64
#define AVM_AND_BASE_L2_GAS 33
#define AVM_OR_BASE_L2_GAS 33
#define AVM_XOR_BASE_L2_GAS 33
#define AVM_NOT_BASE_L2_GAS 27
#define AVM_SHL_BASE_L2_GAS 32
#define AVM_SHR_BASE_L2_GAS 32
#define AVM_CAST_BASE_L2_GAS 30
#define AVM_GETENVVAR_BASE_L2_GAS 20
#define AVM_CALLDATACOPY_BASE_L2_GAS 29
#define AVM_RETURNDATASIZE_BASE_L2_GAS 20
#define AVM_RETURNDATACOPY_BASE_L2_GAS 29
#define AVM_JUMP_BASE_L2_GAS 12
#define AVM_JUMPI_BASE_L2_GAS 18
#define AVM_INTERNALCALL_BASE_L2_GAS 18
#define AVM_INTERNALRETURN_BASE_L2_GAS 18
#define AVM_SET_BASE_L2_GAS 18
#define AVM_MOV_BASE_L2_GAS 23
#define AVM_SLOAD_BASE_L2_GAS 1218
#define AVM_SSTORE_BASE_L2_GAS 2642
#define AVM_NOTEHASHEXISTS_BASE_L2_GAS 1226
#define AVM_EMITNOTEHASH_BASE_L2_GAS 2650
#define AVM_NULLIFIEREXISTS_BASE_L2_GAS 2426
#define AVM_EMITNULLIFIER_BASE_L2_GAS 4250
#define AVM_L1TOL2MSGEXISTS_BASE_L2_GAS 1196
#define AVM_GETCONTRACTINSTANCE_BASE_L2_GAS 2448
#define AVM_EMITUNENCRYPTEDLOG_BASE_L2_GAS 18
#define AVM_SENDL2TOL1MSG_BASE_L2_GAS 226
#define AVM_CALL_BASE_L2_GAS 4845
#define AVM_STATICCALL_BASE_L2_GAS 4845
#define AVM_RETURN_BASE_L2_GAS 28
#define AVM_REVERT_BASE_L2_GAS 28
#define AVM_DEBUGLOG_BASE_L2_GAS 12
#define AVM_DEBUGLOG_DYN_L2_GAS 3
#define AVM_POSEIDON2_BASE_L2_GAS 78
#define AVM_SHA256COMPRESSION_BASE_L2_GAS 261
#define AVM_KECCAKF1600_BASE_L2_GAS 300
#define AVM_ECADD_BASE_L2_GAS 62
#define AVM_MSM_BASE_L2_GAS 1000
#define AVM_TORADIXBE_BASE_L2_GAS 46
#define AVM_CALLDATACOPY_DYN_L2_GAS 6
#define AVM_RETURNDATACOPY_DYN_L2_GAS 6
#define AVM_EMITUNENCRYPTEDLOG_DYN_L2_GAS 146
#define AVM_CALL_DYN_L2_GAS 4
#define AVM_STATICCALL_DYN_L2_GAS 4
#define AVM_RETURN_DYN_L2_GAS 6
#define AVM_REVERT_DYN_L2_GAS 6
#define AVM_MSM_DYN_L2_GAS 100
#define AVM_TORADIXBE_DYN_L2_GAS 20
#define AVM_SSTORE_BASE_DA_GAS 512
#define AVM_EMITNOTEHASH_BASE_DA_GAS 512
#define AVM_EMITNULLIFIER_BASE_DA_GAS 512
#define AVM_SENDL2TOL1MSG_BASE_DA_GAS 512
#define AVM_EMITUNENCRYPTEDLOG_DYN_DA_GAS 512
#define GENERATOR_INDEX__NOTE_HASH_NONCE 2
#define GENERATOR_INDEX__UNIQUE_NOTE_HASH 3
#define GENERATOR_INDEX__SILOED_NOTE_HASH 4
#define GENERATOR_INDEX__OUTER_NULLIFIER 7
#define GENERATOR_INDEX__CONTRACT_ADDRESS_V1 15
#define GENERATOR_INDEX__CONTRACT_LEAF 16
#define GENERATOR_INDEX__PUBLIC_LEAF_INDEX 23
#define GENERATOR_INDEX__PARTIAL_ADDRESS 27
#define GENERATOR_INDEX__PUBLIC_KEYS_HASH 52
