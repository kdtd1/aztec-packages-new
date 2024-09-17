// GENERATED FILE - DO NOT EDIT, RUN yarn remake-constants in circuits.js
#pragma once

#define MAX_NOTE_HASHES_PER_CALL 16
#define MAX_NULLIFIERS_PER_CALL 16
#define MAX_PUBLIC_CALL_STACK_LENGTH_PER_CALL 16
#define MAX_L2_TO_L1_MSGS_PER_CALL 2
#define MAX_PUBLIC_DATA_UPDATE_REQUESTS_PER_CALL 32
#define MAX_PUBLIC_DATA_READS_PER_CALL 32
#define MAX_NOTE_HASH_READ_REQUESTS_PER_CALL 16
#define MAX_NULLIFIER_READ_REQUESTS_PER_CALL 16
#define MAX_NULLIFIER_NON_EXISTENT_READ_REQUESTS_PER_CALL 16
#define MAX_L1_TO_L2_MSG_READ_REQUESTS_PER_CALL 16
#define MAX_UNENCRYPTED_LOGS_PER_CALL 4
#define AZTEC_ADDRESS_LENGTH 1
#define GAS_FEES_LENGTH 2
#define GAS_LENGTH 2
#define CALL_CONTEXT_LENGTH 5
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
#define PUBLIC_CALL_REQUEST_LENGTH 14
#define STATE_REFERENCE_LENGTH 8
#define TOTAL_FEES_LENGTH 1
#define HEADER_LENGTH 24
#define PUBLIC_CIRCUIT_PUBLIC_INPUTS_LENGTH 691
#define PUBLIC_CONTEXT_INPUTS_LENGTH 42
#define AVM_VERIFICATION_KEY_LENGTH_IN_FIELDS 66
#define AVM_PROOF_LENGTH_IN_FIELDS 3802
#define SENDER_SELECTOR 0
#define ADDRESS_SELECTOR 1
#define STORAGE_ADDRESS_SELECTOR 1
#define FUNCTION_SELECTOR_SELECTOR 2
#define START_GLOBAL_VARIABLES 29
#define CHAIN_ID_SELECTOR 29
#define VERSION_SELECTOR 30
#define BLOCK_NUMBER_SELECTOR 31
#define TIMESTAMP_SELECTOR 33
#define FEE_PER_DA_GAS_SELECTOR 36
#define FEE_PER_L2_GAS_SELECTOR 37
#define END_GLOBAL_VARIABLES 38
#define START_SIDE_EFFECT_COUNTER 38
#define TRANSACTION_FEE_SELECTOR 41
#define START_NOTE_HASH_EXISTS_WRITE_OFFSET 0
#define START_NULLIFIER_EXISTS_OFFSET 16
#define START_NULLIFIER_NON_EXISTS_OFFSET 32
#define START_L1_TO_L2_MSG_EXISTS_WRITE_OFFSET 48
#define START_SSTORE_WRITE_OFFSET 64
#define START_SLOAD_WRITE_OFFSET 96
#define START_EMIT_NOTE_HASH_WRITE_OFFSET 128
#define START_EMIT_NULLIFIER_WRITE_OFFSET 144
#define START_EMIT_L2_TO_L1_MSG_WRITE_OFFSET 160
#define START_EMIT_UNENCRYPTED_LOG_WRITE_OFFSET 162
#define AVM_DEFAULT_BASE_GAS_L2 100
#define AVM_DEFAULT_DYN_GAS_L2 0
#define AVM_ADD_BASE_L2_GAS 320
#define AVM_SUB_BASE_L2_GAS 320
#define AVM_MUL_BASE_L2_GAS 330
#define AVM_DIV_BASE_L2_GAS 430
#define AVM_FDIV_BASE_L2_GAS 320
#define AVM_EQ_BASE_L2_GAS 320
#define AVM_LT_BASE_L2_GAS 640
#define AVM_LTE_BASE_L2_GAS 640
#define AVM_AND_BASE_L2_GAS 330
#define AVM_OR_BASE_L2_GAS 330
#define AVM_XOR_BASE_L2_GAS 320
#define AVM_NOT_BASE_L2_GAS 270
#define AVM_SHL_BASE_L2_GAS 320
#define AVM_SHR_BASE_L2_GAS 320
#define AVM_CAST_BASE_L2_GAS 300
#define AVM_ADDRESS_BASE_L2_GAS 200
#define AVM_STORAGEADDRESS_BASE_L2_GAS 200
#define AVM_SENDER_BASE_L2_GAS 200
#define AVM_FUNCTIONSELECTOR_BASE_L2_GAS 200
#define AVM_TRANSACTIONFEE_BASE_L2_GAS 200
#define AVM_CHAINID_BASE_L2_GAS 200
#define AVM_VERSION_BASE_L2_GAS 200
#define AVM_BLOCKNUMBER_BASE_L2_GAS 200
#define AVM_TIMESTAMP_BASE_L2_GAS 200
#define AVM_FEEPERL2GAS_BASE_L2_GAS 200
#define AVM_FEEPERDAGAS_BASE_L2_GAS 200
#define AVM_CALLDATACOPY_BASE_L2_GAS 290
#define AVM_L2GASLEFT_BASE_L2_GAS 180
#define AVM_DAGASLEFT_BASE_L2_GAS 180
#define AVM_JUMP_BASE_L2_GAS 120
#define AVM_JUMPI_BASE_L2_GAS 180
#define AVM_INTERNALCALL_BASE_L2_GAS 180
#define AVM_INTERNALRETURN_BASE_L2_GAS 180
#define AVM_SET_BASE_L2_GAS 180
#define AVM_MOV_BASE_L2_GAS 230
#define AVM_CMOV_BASE_L2_GAS 340
#define AVM_SLOAD_BASE_L2_GAS 180
#define AVM_SSTORE_BASE_L2_GAS 180
#define AVM_NOTEHASHEXISTS_BASE_L2_GAS 260
#define AVM_EMITNOTEHASH_BASE_L2_GAS 260
#define AVM_NULLIFIEREXISTS_BASE_L2_GAS 260
#define AVM_EMITNULLIFIER_BASE_L2_GAS 260
#define AVM_L1TOL2MSGEXISTS_BASE_L2_GAS 260
#define AVM_GETCONTRACTINSTANCE_BASE_L2_GAS 480
#define AVM_EMITUNENCRYPTEDLOG_BASE_L2_GAS 180
#define AVM_SENDL2TOL1MSG_BASE_L2_GAS 260
#define AVM_CALL_BASE_L2_GAS 450
#define AVM_STATICCALL_BASE_L2_GAS 450
#define AVM_DELEGATECALL_BASE_L2_GAS 0
#define AVM_RETURN_BASE_L2_GAS 140
#define AVM_REVERT_BASE_L2_GAS 140
#define AVM_DEBUGLOG_BASE_L2_GAS 100
#define AVM_KECCAK_BASE_L2_GAS 3000
#define AVM_POSEIDON2_BASE_L2_GAS 670
#define AVM_SHA256_BASE_L2_GAS 3000
#define AVM_PEDERSEN_BASE_L2_GAS 3000
#define AVM_ECADD_BASE_L2_GAS 900
#define AVM_MSM_BASE_L2_GAS 900
#define AVM_PEDERSENCOMMITMENT_BASE_L2_GAS 3000
#define AVM_TORADIXLE_BASE_L2_GAS 200
#define AVM_SHA256COMPRESSION_BASE_L2_GAS 3000
#define AVM_KECCAKF1600_BASE_L2_GAS 3000
#define AVM_ADD_DYN_L2_GAS 0
#define AVM_SUB_DYN_L2_GAS 0
#define AVM_MUL_DYN_L2_GAS 0
#define AVM_DIV_DYN_L2_GAS 0
#define AVM_FDIV_DYN_L2_GAS 0
#define AVM_EQ_DYN_L2_GAS 0
#define AVM_LT_DYN_L2_GAS 0
#define AVM_LTE_DYN_L2_GAS 0
#define AVM_AND_DYN_L2_GAS 0
#define AVM_OR_DYN_L2_GAS 0
#define AVM_XOR_DYN_L2_GAS 0
#define AVM_NOT_DYN_L2_GAS 0
#define AVM_SHL_DYN_L2_GAS 0
#define AVM_SHR_DYN_L2_GAS 0
#define AVM_CAST_DYN_L2_GAS 0
#define AVM_ADDRESS_DYN_L2_GAS 0
#define AVM_STORAGEADDRESS_DYN_L2_GAS 0
#define AVM_SENDER_DYN_L2_GAS 0
#define AVM_FUNCTIONSELECTOR_DYN_L2_GAS 0
#define AVM_TRANSACTIONFEE_DYN_L2_GAS 0
#define AVM_CHAINID_DYN_L2_GAS 0
#define AVM_VERSION_DYN_L2_GAS 0
#define AVM_BLOCKNUMBER_DYN_L2_GAS 0
#define AVM_TIMESTAMP_DYN_L2_GAS 0
#define AVM_FEEPERL2GAS_DYN_L2_GAS 0
#define AVM_FEEPERDAGAS_DYN_L2_GAS 0
#define AVM_CALLDATACOPY_DYN_L2_GAS 50
#define AVM_L2GASLEFT_DYN_L2_GAS 0
#define AVM_DAGASLEFT_DYN_L2_GAS 0
#define AVM_JUMP_DYN_L2_GAS 0
#define AVM_JUMPI_DYN_L2_GAS 0
#define AVM_INTERNALCALL_DYN_L2_GAS 0
#define AVM_INTERNALRETURN_DYN_L2_GAS 0
#define AVM_SET_DYN_L2_GAS 0
#define AVM_MOV_DYN_L2_GAS 0
#define AVM_CMOV_DYN_L2_GAS 0
#define AVM_SLOAD_DYN_L2_GAS 180
#define AVM_SSTORE_DYN_L2_GAS 180
#define AVM_NOTEHASHEXISTS_DYN_L2_GAS 0
#define AVM_EMITNOTEHASH_DYN_L2_GAS 0
#define AVM_NULLIFIEREXISTS_DYN_L2_GAS 0
#define AVM_EMITNULLIFIER_DYN_L2_GAS 0
#define AVM_L1TOL2MSGEXISTS_DYN_L2_GAS 0
#define AVM_GETCONTRACTINSTANCE_DYN_L2_GAS 0
#define AVM_EMITUNENCRYPTEDLOG_DYN_L2_GAS 180
#define AVM_SENDL2TOL1MSG_DYN_L2_GAS 0
#define AVM_CALL_DYN_L2_GAS 50
#define AVM_STATICCALL_DYN_L2_GAS 50
#define AVM_DELEGATECALL_DYN_L2_GAS 50
#define AVM_RETURN_DYN_L2_GAS 50
#define AVM_REVERT_DYN_L2_GAS 50
#define AVM_DEBUGLOG_DYN_L2_GAS 0
#define AVM_KECCAK_DYN_L2_GAS 0
#define AVM_POSEIDON2_DYN_L2_GAS 0
#define AVM_SHA256_DYN_L2_GAS 0
#define AVM_PEDERSEN_DYN_L2_GAS 0
#define AVM_ECADD_DYN_L2_GAS 0
#define AVM_MSM_DYN_L2_GAS 0
#define AVM_PEDERSENCOMMITMENT_DYN_L2_GAS 0
#define AVM_TORADIXLE_DYN_L2_GAS 200
#define AVM_SHA256COMPRESSION_DYN_L2_GAS 0
#define AVM_KECCAKF1600_DYN_L2_GAS 0
