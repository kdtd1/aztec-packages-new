#include "barretenberg/vm2/common/instruction_spec.hpp"

#include "barretenberg/vm/aztec_constants.hpp" // Move over.
#include "barretenberg/vm2/common/opcodes.hpp"

#include <array>

namespace bb::avm2 {

namespace {
// This structure is code-generated (but manually set) by the test: DecompositionSelectors.CodeGen
const std::unordered_map<WireOpCode, std::array<uint8_t, NUM_OP_DC_SELECTORS>> WireOpCode_DC_SELECTORS = {
    { WireOpCode::ADD_8, { 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0 } },
    { WireOpCode::ADD_16, { 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },
    { WireOpCode::SUB_8, { 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0 } },
    { WireOpCode::SUB_16, { 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },
    { WireOpCode::MUL_8, { 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0 } },
    { WireOpCode::MUL_16, { 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },
    { WireOpCode::DIV_8, { 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0 } },
    { WireOpCode::DIV_16, { 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },
    { WireOpCode::FDIV_8, { 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0 } },
    { WireOpCode::FDIV_16, { 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },
    { WireOpCode::EQ_8, { 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0 } },
    { WireOpCode::EQ_16, { 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },
    { WireOpCode::LT_8, { 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0 } },
    { WireOpCode::LT_16, { 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },
    { WireOpCode::LTE_8, { 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0 } },
    { WireOpCode::LTE_16, { 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },
    { WireOpCode::AND_8, { 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0 } },
    { WireOpCode::AND_16, { 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },
    { WireOpCode::OR_8, { 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0 } },
    { WireOpCode::OR_16, { 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },
    { WireOpCode::XOR_8, { 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0 } },
    { WireOpCode::XOR_16, { 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },
    { WireOpCode::NOT_8, { 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },
    { WireOpCode::NOT_16, { 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },
    { WireOpCode::SHL_8, { 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0 } },
    { WireOpCode::SHL_16, { 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },
    { WireOpCode::SHR_8, { 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0 } },
    { WireOpCode::SHR_16, { 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },
    { WireOpCode::CAST_8, { 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0 } },
    { WireOpCode::CAST_16, { 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 } },
    { WireOpCode::GETENVVAR_16, { 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },
    { WireOpCode::CALLDATACOPY, { 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },
    { WireOpCode::SUCCESSCOPY, { 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },
    { WireOpCode::RETURNDATASIZE, { 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },
    { WireOpCode::RETURNDATACOPY, { 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },
    { WireOpCode::JUMP_32, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0 } },
    { WireOpCode::JUMPI_32, { 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0 } },
    { WireOpCode::INTERNALCALL, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0 } },
    { WireOpCode::INTERNALRETURN, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },
    { WireOpCode::SET_8, { 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0 } },
    { WireOpCode::SET_16, { 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0 } },
    { WireOpCode::SET_32, { 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0 } },
    { WireOpCode::SET_64, { 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0 } },
    { WireOpCode::SET_128, { 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0 } },
    { WireOpCode::SET_FF, { 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0 } },
    { WireOpCode::MOV_8, { 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },
    { WireOpCode::MOV_16, { 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },
    { WireOpCode::SLOAD, { 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },
    { WireOpCode::SSTORE, { 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },
    { WireOpCode::NOTEHASHEXISTS, { 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },
    { WireOpCode::EMITNOTEHASH, { 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },
    { WireOpCode::NULLIFIEREXISTS, { 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },
    { WireOpCode::EMITNULLIFIER, { 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },
    { WireOpCode::L1TOL2MSGEXISTS, { 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },
    { WireOpCode::GETCONTRACTINSTANCE, { 0, 0, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },
    { WireOpCode::EMITUNENCRYPTEDLOG, { 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },
    { WireOpCode::SENDL2TOL1MSG, { 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },
    { WireOpCode::CALL, { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },
    { WireOpCode::STATICCALL, { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },
    { WireOpCode::RETURN, { 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },
    { WireOpCode::REVERT_8, { 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },
    { WireOpCode::REVERT_16, { 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },
    { WireOpCode::DEBUGLOG, { 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },
    { WireOpCode::POSEIDON2PERM, { 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },
    { WireOpCode::SHA256COMPRESSION, { 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },
    { WireOpCode::KECCAKF1600, { 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },
    { WireOpCode::ECADD, { 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },
    { WireOpCode::TORADIXBE, { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },
};

} // anonymous namespace

const std::unordered_map<WireOpCode, WireInstructionSpec> WIRE_INSTRUCTION_SPEC = {
    { WireOpCode::ADD_8,
      { .exec_opcode = ExecutionOpCode::ADD, .op_dc_selectors = WireOpCode_DC_SELECTORS.at(WireOpCode::ADD_8) } },
    { WireOpCode::ADD_16,
      { .exec_opcode = ExecutionOpCode::ADD, .op_dc_selectors = WireOpCode_DC_SELECTORS.at(WireOpCode::ADD_16) } },
    { WireOpCode::SUB_8,
      { .exec_opcode = ExecutionOpCode::SUB, .op_dc_selectors = WireOpCode_DC_SELECTORS.at(WireOpCode::SUB_8) } },
    { WireOpCode::SUB_16,
      { .exec_opcode = ExecutionOpCode::SUB, .op_dc_selectors = WireOpCode_DC_SELECTORS.at(WireOpCode::SUB_16) } },
    { WireOpCode::MUL_8,
      { .exec_opcode = ExecutionOpCode::MUL, .op_dc_selectors = WireOpCode_DC_SELECTORS.at(WireOpCode::MUL_8) } },
    { WireOpCode::MUL_16,
      { .exec_opcode = ExecutionOpCode::MUL, .op_dc_selectors = WireOpCode_DC_SELECTORS.at(WireOpCode::MUL_16) } },
    { WireOpCode::DIV_8,
      { .exec_opcode = ExecutionOpCode::DIV, .op_dc_selectors = WireOpCode_DC_SELECTORS.at(WireOpCode::DIV_8) } },
    { WireOpCode::DIV_16,
      { .exec_opcode = ExecutionOpCode::DIV, .op_dc_selectors = WireOpCode_DC_SELECTORS.at(WireOpCode::DIV_16) } },
    { WireOpCode::FDIV_8,
      { .exec_opcode = ExecutionOpCode::FDIV, .op_dc_selectors = WireOpCode_DC_SELECTORS.at(WireOpCode::FDIV_8) } },
    { WireOpCode::FDIV_16,
      { .exec_opcode = ExecutionOpCode::FDIV, .op_dc_selectors = WireOpCode_DC_SELECTORS.at(WireOpCode::FDIV_16) } },
    { WireOpCode::EQ_8,
      { .exec_opcode = ExecutionOpCode::EQ, .op_dc_selectors = WireOpCode_DC_SELECTORS.at(WireOpCode::EQ_8) } },
    { WireOpCode::EQ_16,
      { .exec_opcode = ExecutionOpCode::EQ, .op_dc_selectors = WireOpCode_DC_SELECTORS.at(WireOpCode::EQ_16) } },
    { WireOpCode::LT_8,
      { .exec_opcode = ExecutionOpCode::LT, .op_dc_selectors = WireOpCode_DC_SELECTORS.at(WireOpCode::LT_8) } },
    { WireOpCode::LT_16,
      { .exec_opcode = ExecutionOpCode::LT, .op_dc_selectors = WireOpCode_DC_SELECTORS.at(WireOpCode::LT_16) } },
    { WireOpCode::LTE_8,
      { .exec_opcode = ExecutionOpCode::LTE, .op_dc_selectors = WireOpCode_DC_SELECTORS.at(WireOpCode::LTE_8) } },
    { WireOpCode::LTE_16,
      { .exec_opcode = ExecutionOpCode::LTE, .op_dc_selectors = WireOpCode_DC_SELECTORS.at(WireOpCode::LTE_16) } },
    { WireOpCode::AND_8,
      { .exec_opcode = ExecutionOpCode::AND, .op_dc_selectors = WireOpCode_DC_SELECTORS.at(WireOpCode::AND_8) } },
    { WireOpCode::AND_16,
      { .exec_opcode = ExecutionOpCode::AND, .op_dc_selectors = WireOpCode_DC_SELECTORS.at(WireOpCode::AND_16) } },
    { WireOpCode::OR_8,
      { .exec_opcode = ExecutionOpCode::OR, .op_dc_selectors = WireOpCode_DC_SELECTORS.at(WireOpCode::OR_8) } },
    { WireOpCode::OR_16,
      { .exec_opcode = ExecutionOpCode::OR, .op_dc_selectors = WireOpCode_DC_SELECTORS.at(WireOpCode::OR_16) } },
    { WireOpCode::XOR_8,
      { .exec_opcode = ExecutionOpCode::XOR, .op_dc_selectors = WireOpCode_DC_SELECTORS.at(WireOpCode::XOR_8) } },
    { WireOpCode::XOR_16,
      { .exec_opcode = ExecutionOpCode::XOR, .op_dc_selectors = WireOpCode_DC_SELECTORS.at(WireOpCode::XOR_16) } },
    { WireOpCode::NOT_8,
      { .exec_opcode = ExecutionOpCode::NOT, .op_dc_selectors = WireOpCode_DC_SELECTORS.at(WireOpCode::NOT_8) } },
    { WireOpCode::NOT_16,
      { .exec_opcode = ExecutionOpCode::NOT, .op_dc_selectors = WireOpCode_DC_SELECTORS.at(WireOpCode::NOT_16) } },
    { WireOpCode::SHL_8,
      { .exec_opcode = ExecutionOpCode::SHL, .op_dc_selectors = WireOpCode_DC_SELECTORS.at(WireOpCode::SHL_8) } },
    { WireOpCode::SHL_16,
      { .exec_opcode = ExecutionOpCode::SHL, .op_dc_selectors = WireOpCode_DC_SELECTORS.at(WireOpCode::SHL_16) } },
    { WireOpCode::SHR_8,
      { .exec_opcode = ExecutionOpCode::SHR, .op_dc_selectors = WireOpCode_DC_SELECTORS.at(WireOpCode::SHR_8) } },
    { WireOpCode::SHR_16,
      { .exec_opcode = ExecutionOpCode::SHR, .op_dc_selectors = WireOpCode_DC_SELECTORS.at(WireOpCode::SHR_16) } },
    { WireOpCode::CAST_8,
      { .exec_opcode = ExecutionOpCode::CAST, .op_dc_selectors = WireOpCode_DC_SELECTORS.at(WireOpCode::CAST_8) } },
    { WireOpCode::CAST_16,
      { .exec_opcode = ExecutionOpCode::CAST, .op_dc_selectors = WireOpCode_DC_SELECTORS.at(WireOpCode::CAST_16) } },
    { WireOpCode::GETENVVAR_16,
      { .exec_opcode = ExecutionOpCode::GETENVVAR,
        .op_dc_selectors = WireOpCode_DC_SELECTORS.at(WireOpCode::GETENVVAR_16) } },
    { WireOpCode::CALLDATACOPY,
      { .exec_opcode = ExecutionOpCode::CALLDATACOPY,
        .op_dc_selectors = WireOpCode_DC_SELECTORS.at(WireOpCode::CALLDATACOPY) } },
    { WireOpCode::SUCCESSCOPY,
      { .exec_opcode = ExecutionOpCode::SUCCESSCOPY,
        .op_dc_selectors = WireOpCode_DC_SELECTORS.at(WireOpCode::SUCCESSCOPY) } },
    { WireOpCode::RETURNDATASIZE,
      { .exec_opcode = ExecutionOpCode::RETURNDATASIZE,
        .op_dc_selectors = WireOpCode_DC_SELECTORS.at(WireOpCode::RETURNDATASIZE) } },
    { WireOpCode::RETURNDATACOPY,
      { .exec_opcode = ExecutionOpCode::RETURNDATACOPY,
        .op_dc_selectors = WireOpCode_DC_SELECTORS.at(WireOpCode::RETURNDATACOPY) } },
    { WireOpCode::JUMP_32,
      { .exec_opcode = ExecutionOpCode::JUMP, .op_dc_selectors = WireOpCode_DC_SELECTORS.at(WireOpCode::JUMP_32) } },
    { WireOpCode::JUMPI_32,
      { .exec_opcode = ExecutionOpCode::JUMPI, .op_dc_selectors = WireOpCode_DC_SELECTORS.at(WireOpCode::JUMPI_32) } },
    { WireOpCode::INTERNALCALL,
      { .exec_opcode = ExecutionOpCode::INTERNALCALL,
        .op_dc_selectors = WireOpCode_DC_SELECTORS.at(WireOpCode::INTERNALCALL) } },
    { WireOpCode::INTERNALRETURN,
      { .exec_opcode = ExecutionOpCode::INTERNALRETURN,
        .op_dc_selectors = WireOpCode_DC_SELECTORS.at(WireOpCode::INTERNALRETURN) } },
    { WireOpCode::SET_8,
      { .exec_opcode = ExecutionOpCode::SET, .op_dc_selectors = WireOpCode_DC_SELECTORS.at(WireOpCode::SET_8) } },
    { WireOpCode::SET_16,
      { .exec_opcode = ExecutionOpCode::SET, .op_dc_selectors = WireOpCode_DC_SELECTORS.at(WireOpCode::SET_16) } },
    { WireOpCode::SET_32,
      { .exec_opcode = ExecutionOpCode::SET, .op_dc_selectors = WireOpCode_DC_SELECTORS.at(WireOpCode::SET_32) } },
    { WireOpCode::SET_64,
      { .exec_opcode = ExecutionOpCode::SET, .op_dc_selectors = WireOpCode_DC_SELECTORS.at(WireOpCode::SET_64) } },
    { WireOpCode::SET_128,
      { .exec_opcode = ExecutionOpCode::SET, .op_dc_selectors = WireOpCode_DC_SELECTORS.at(WireOpCode::SET_128) } },
    { WireOpCode::SET_FF,
      { .exec_opcode = ExecutionOpCode::SET, .op_dc_selectors = WireOpCode_DC_SELECTORS.at(WireOpCode::SET_FF) } },
    { WireOpCode::MOV_8,
      { .exec_opcode = ExecutionOpCode::MOV, .op_dc_selectors = WireOpCode_DC_SELECTORS.at(WireOpCode::MOV_8) } },
    { WireOpCode::MOV_16,
      { .exec_opcode = ExecutionOpCode::MOV, .op_dc_selectors = WireOpCode_DC_SELECTORS.at(WireOpCode::MOV_16) } },
    { WireOpCode::SLOAD,
      { .exec_opcode = ExecutionOpCode::SLOAD, .op_dc_selectors = WireOpCode_DC_SELECTORS.at(WireOpCode::SLOAD) } },
    { WireOpCode::SSTORE,
      { .exec_opcode = ExecutionOpCode::SSTORE, .op_dc_selectors = WireOpCode_DC_SELECTORS.at(WireOpCode::SSTORE) } },
    { WireOpCode::NOTEHASHEXISTS,
      { .exec_opcode = ExecutionOpCode::NOTEHASHEXISTS,
        .op_dc_selectors = WireOpCode_DC_SELECTORS.at(WireOpCode::NOTEHASHEXISTS) } },
    { WireOpCode::EMITNOTEHASH,
      { .exec_opcode = ExecutionOpCode::EMITNOTEHASH,
        .op_dc_selectors = WireOpCode_DC_SELECTORS.at(WireOpCode::EMITNOTEHASH) } },
    { WireOpCode::NULLIFIEREXISTS,
      { .exec_opcode = ExecutionOpCode::NULLIFIEREXISTS,
        .op_dc_selectors = WireOpCode_DC_SELECTORS.at(WireOpCode::NULLIFIEREXISTS) } },
    { WireOpCode::EMITNULLIFIER,
      { .exec_opcode = ExecutionOpCode::EMITNULLIFIER,
        .op_dc_selectors = WireOpCode_DC_SELECTORS.at(WireOpCode::EMITNULLIFIER) } },
    { WireOpCode::L1TOL2MSGEXISTS,
      { .exec_opcode = ExecutionOpCode::L1TOL2MSGEXISTS,
        .op_dc_selectors = WireOpCode_DC_SELECTORS.at(WireOpCode::L1TOL2MSGEXISTS) } },
    { WireOpCode::GETCONTRACTINSTANCE,
      { .exec_opcode = ExecutionOpCode::GETCONTRACTINSTANCE,
        .op_dc_selectors = WireOpCode_DC_SELECTORS.at(WireOpCode::GETCONTRACTINSTANCE) } },
    { WireOpCode::EMITUNENCRYPTEDLOG,
      { .exec_opcode = ExecutionOpCode::EMITUNENCRYPTEDLOG,
        .op_dc_selectors = WireOpCode_DC_SELECTORS.at(WireOpCode::EMITUNENCRYPTEDLOG) } },
    { WireOpCode::SENDL2TOL1MSG,
      { .exec_opcode = ExecutionOpCode::SENDL2TOL1MSG,
        .op_dc_selectors = WireOpCode_DC_SELECTORS.at(WireOpCode::SENDL2TOL1MSG) } },
    { WireOpCode::CALL,
      { .exec_opcode = ExecutionOpCode::CALL, .op_dc_selectors = WireOpCode_DC_SELECTORS.at(WireOpCode::CALL) } },
    { WireOpCode::STATICCALL,
      { .exec_opcode = ExecutionOpCode::STATICCALL,
        .op_dc_selectors = WireOpCode_DC_SELECTORS.at(WireOpCode::STATICCALL) } },
    { WireOpCode::RETURN,
      { .exec_opcode = ExecutionOpCode::RETURN, .op_dc_selectors = WireOpCode_DC_SELECTORS.at(WireOpCode::RETURN) } },
    { WireOpCode::REVERT_8,
      { .exec_opcode = ExecutionOpCode::REVERT, .op_dc_selectors = WireOpCode_DC_SELECTORS.at(WireOpCode::REVERT_8) } },
    { WireOpCode::REVERT_16,
      { .exec_opcode = ExecutionOpCode::REVERT,
        .op_dc_selectors = WireOpCode_DC_SELECTORS.at(WireOpCode::REVERT_16) } },
    { WireOpCode::DEBUGLOG,
      { .exec_opcode = ExecutionOpCode::DEBUGLOG,
        .op_dc_selectors = WireOpCode_DC_SELECTORS.at(WireOpCode::DEBUGLOG) } },
    { WireOpCode::POSEIDON2PERM,
      { .exec_opcode = ExecutionOpCode::POSEIDON2PERM,
        .op_dc_selectors = WireOpCode_DC_SELECTORS.at(WireOpCode::POSEIDON2PERM) } },
    { WireOpCode::SHA256COMPRESSION,
      { .exec_opcode = ExecutionOpCode::SHA256COMPRESSION,
        .op_dc_selectors = WireOpCode_DC_SELECTORS.at(WireOpCode::SHA256COMPRESSION) } },
    { WireOpCode::KECCAKF1600,
      { .exec_opcode = ExecutionOpCode::KECCAKF1600,
        .op_dc_selectors = WireOpCode_DC_SELECTORS.at(WireOpCode::KECCAKF1600) } },
    { WireOpCode::ECADD,
      { .exec_opcode = ExecutionOpCode::ECADD, .op_dc_selectors = WireOpCode_DC_SELECTORS.at(WireOpCode::ECADD) } },
    { WireOpCode::TORADIXBE,
      { .exec_opcode = ExecutionOpCode::TORADIXBE,
        .op_dc_selectors = WireOpCode_DC_SELECTORS.at(WireOpCode::TORADIXBE) } },
};

const std::unordered_map<WireOpCode, ExecutionOpCode> OPCODE_MAP = {
    { WireOpCode::ADD_8, ExecutionOpCode::ADD },    { WireOpCode::ADD_16, ExecutionOpCode::ADD },
    { WireOpCode::CALL, ExecutionOpCode::CALL },    { WireOpCode::RETURN, ExecutionOpCode::RETURN },
    { WireOpCode::JUMP_32, ExecutionOpCode::JUMP }, { WireOpCode::JUMPI_32, ExecutionOpCode::JUMPI },
    { WireOpCode::SET_8, ExecutionOpCode::SET },    { WireOpCode::SET_16, ExecutionOpCode::SET },
    { WireOpCode::SET_32, ExecutionOpCode::SET },   { WireOpCode::SET_64, ExecutionOpCode::SET },
    { WireOpCode::SET_128, ExecutionOpCode::SET },  { WireOpCode::SET_FF, ExecutionOpCode::SET },
    { WireOpCode::MOV_8, ExecutionOpCode::MOV },    { WireOpCode::MOV_16, ExecutionOpCode::MOV },
};

const std::unordered_map<ExecutionOpCode, ExecInstructionSpec> EXEC_INSTRUCTION_SPEC = {
    { ExecutionOpCode::ADD,
      { .num_addresses = 3, .gas_cost = { .base_l2 = AVM_ADD_BASE_L2_GAS, .base_da = 0, .dyn_l2 = 0, .dyn_da = 0 } } },
    { ExecutionOpCode::SET,
      { .num_addresses = 1, .gas_cost = { .base_l2 = AVM_SET_BASE_L2_GAS, .base_da = 0, .dyn_l2 = 0, .dyn_da = 0 } } },
    { ExecutionOpCode::MOV,
      { .num_addresses = 2, .gas_cost = { .base_l2 = AVM_MOV_BASE_L2_GAS, .base_da = 0, .dyn_l2 = 0, .dyn_da = 0 } } },
    { ExecutionOpCode::CALL,
      { .num_addresses = 5,
        .gas_cost = { .base_l2 = AVM_CALL_BASE_L2_GAS, .base_da = 0, .dyn_l2 = AVM_CALL_DYN_L2_GAS, .dyn_da = 0 } } },
    { ExecutionOpCode::RETURN,
      { .num_addresses = 2,
        .gas_cost = { .base_l2 = AVM_RETURN_BASE_L2_GAS,
                      .base_da = 0,
                      .dyn_l2 = AVM_RETURN_DYN_L2_GAS,
                      .dyn_da = 0 } } },
    { ExecutionOpCode::JUMP,
      { .num_addresses = 0, .gas_cost = { .base_l2 = AVM_JUMP_BASE_L2_GAS, .base_da = 0, .dyn_l2 = 0, .dyn_da = 0 } } },
    { ExecutionOpCode::JUMPI,
      { .num_addresses = 1,
        .gas_cost = { .base_l2 = AVM_JUMPI_BASE_L2_GAS, .base_da = 0, .dyn_l2 = 0, .dyn_da = 0 } } },
};

} // namespace bb::avm2
