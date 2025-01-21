// AUTOGENERATED FILE
#include "flavor.hpp"

namespace bb::avm2 {

AvmFlavor::AllConstRefValues::AllConstRefValues(
    const RefArray<AvmFlavor::AllConstRefValues::BaseDataType, AvmFlavor::NUM_ALL_ENTITIES>& il)
    : precomputed_bitwise_input_a(il[0])
    , precomputed_bitwise_input_b(il[1])
    , precomputed_bitwise_op_id(il[2])
    , precomputed_bitwise_output(il[3])
    , precomputed_clk(il[4])
    , precomputed_first_row(il[5])
    , precomputed_sel_bitwise(il[6])
    , execution_input(il[7])
    , alu_dst_addr(il[8])
    , alu_ia(il[9])
    , alu_ia_addr(il[10])
    , alu_ib(il[11])
    , alu_ib_addr(il[12])
    , alu_ic(il[13])
    , alu_op(il[14])
    , alu_sel_op_add(il[15])
    , execution_addressing_error_idx(il[16])
    , execution_addressing_error_kind(il[17])
    , execution_base_address_tag(il[18])
    , execution_base_address_val(il[19])
    , execution_bytecode_id(il[20])
    , execution_clk(il[21])
    , execution_ex_opcode(il[22])
    , execution_indirect(il[23])
    , execution_last(il[24])
    , execution_op1(il[25])
    , execution_op1_after_relative(il[26])
    , execution_op2(il[27])
    , execution_op2_after_relative(il[28])
    , execution_op3(il[29])
    , execution_op3_after_relative(il[30])
    , execution_op4(il[31])
    , execution_op4_after_relative(il[32])
    , execution_pc(il[33])
    , execution_rop1(il[34])
    , execution_rop2(il[35])
    , execution_rop3(il[36])
    , execution_rop4(il[37])
    , execution_sel(il[38])
    , execution_sel_addressing_error(il[39])
    , execution_sel_op1_is_address(il[40])
    , execution_sel_op2_is_address(il[41])
    , execution_sel_op3_is_address(il[42])
    , execution_sel_op4_is_address(il[43])
    , lookup_dummy_precomputed_counts(il[44])
    , lookup_dummy_dynamic_counts(il[45])
    , perm_dummy_dynamic_inv(il[46])
    , lookup_dummy_precomputed_inv(il[47])
    , lookup_dummy_dynamic_inv(il[48])
    , execution_sel_shift(il[49])
{}

AvmFlavor::ProverPolynomials::ProverPolynomials(ProvingKey& proving_key)
{
    for (auto [prover_poly, key_poly] : zip_view(this->get_unshifted(), proving_key.get_all())) {
        ASSERT(flavor_get_label(*this, prover_poly) == flavor_get_label(proving_key, key_poly));
        prover_poly = key_poly.share();
    }
    for (auto [prover_poly, key_poly] : zip_view(this->get_shifted(), proving_key.get_to_be_shifted())) {
        ASSERT(flavor_get_label(*this, prover_poly) == (flavor_get_label(proving_key, key_poly) + "_shift"));
        prover_poly = key_poly.shifted();
    }
}

AvmFlavor::AllConstRefValues AvmFlavor::ProverPolynomials::get_row(size_t row_idx) const
{
    return RefArray{ precomputed_bitwise_input_a[row_idx],
                     precomputed_bitwise_input_b[row_idx],
                     precomputed_bitwise_op_id[row_idx],
                     precomputed_bitwise_output[row_idx],
                     precomputed_clk[row_idx],
                     precomputed_first_row[row_idx],
                     precomputed_sel_bitwise[row_idx],
                     execution_input[row_idx],
                     alu_dst_addr[row_idx],
                     alu_ia[row_idx],
                     alu_ia_addr[row_idx],
                     alu_ib[row_idx],
                     alu_ib_addr[row_idx],
                     alu_ic[row_idx],
                     alu_op[row_idx],
                     alu_sel_op_add[row_idx],
                     execution_addressing_error_idx[row_idx],
                     execution_addressing_error_kind[row_idx],
                     execution_base_address_tag[row_idx],
                     execution_base_address_val[row_idx],
                     execution_bytecode_id[row_idx],
                     execution_clk[row_idx],
                     execution_ex_opcode[row_idx],
                     execution_indirect[row_idx],
                     execution_last[row_idx],
                     execution_op1[row_idx],
                     execution_op1_after_relative[row_idx],
                     execution_op2[row_idx],
                     execution_op2_after_relative[row_idx],
                     execution_op3[row_idx],
                     execution_op3_after_relative[row_idx],
                     execution_op4[row_idx],
                     execution_op4_after_relative[row_idx],
                     execution_pc[row_idx],
                     execution_rop1[row_idx],
                     execution_rop2[row_idx],
                     execution_rop3[row_idx],
                     execution_rop4[row_idx],
                     execution_sel[row_idx],
                     execution_sel_addressing_error[row_idx],
                     execution_sel_op1_is_address[row_idx],
                     execution_sel_op2_is_address[row_idx],
                     execution_sel_op3_is_address[row_idx],
                     execution_sel_op4_is_address[row_idx],
                     lookup_dummy_precomputed_counts[row_idx],
                     lookup_dummy_dynamic_counts[row_idx],
                     perm_dummy_dynamic_inv[row_idx],
                     lookup_dummy_precomputed_inv[row_idx],
                     lookup_dummy_dynamic_inv[row_idx],
                     execution_sel_shift[row_idx] };
}

AvmFlavor::CommitmentLabels::CommitmentLabels()
{
    Base::precomputed_bitwise_input_a = "PRECOMPUTED_BITWISE_INPUT_A";
    Base::precomputed_bitwise_input_b = "PRECOMPUTED_BITWISE_INPUT_B";
    Base::precomputed_bitwise_op_id = "PRECOMPUTED_BITWISE_OP_ID";
    Base::precomputed_bitwise_output = "PRECOMPUTED_BITWISE_OUTPUT";
    Base::precomputed_clk = "PRECOMPUTED_CLK";
    Base::precomputed_first_row = "PRECOMPUTED_FIRST_ROW";
    Base::precomputed_sel_bitwise = "PRECOMPUTED_SEL_BITWISE";
    Base::execution_input = "EXECUTION_INPUT";
    Base::alu_dst_addr = "ALU_DST_ADDR";
    Base::alu_ia = "ALU_IA";
    Base::alu_ia_addr = "ALU_IA_ADDR";
    Base::alu_ib = "ALU_IB";
    Base::alu_ib_addr = "ALU_IB_ADDR";
    Base::alu_ic = "ALU_IC";
    Base::alu_op = "ALU_OP";
    Base::alu_sel_op_add = "ALU_SEL_OP_ADD";
    Base::execution_addressing_error_idx = "EXECUTION_ADDRESSING_ERROR_IDX";
    Base::execution_addressing_error_kind = "EXECUTION_ADDRESSING_ERROR_KIND";
    Base::execution_base_address_tag = "EXECUTION_BASE_ADDRESS_TAG";
    Base::execution_base_address_val = "EXECUTION_BASE_ADDRESS_VAL";
    Base::execution_bytecode_id = "EXECUTION_BYTECODE_ID";
    Base::execution_clk = "EXECUTION_CLK";
    Base::execution_ex_opcode = "EXECUTION_EX_OPCODE";
    Base::execution_indirect = "EXECUTION_INDIRECT";
    Base::execution_last = "EXECUTION_LAST";
    Base::execution_op1 = "EXECUTION_OP1";
    Base::execution_op1_after_relative = "EXECUTION_OP1_AFTER_RELATIVE";
    Base::execution_op2 = "EXECUTION_OP2";
    Base::execution_op2_after_relative = "EXECUTION_OP2_AFTER_RELATIVE";
    Base::execution_op3 = "EXECUTION_OP3";
    Base::execution_op3_after_relative = "EXECUTION_OP3_AFTER_RELATIVE";
    Base::execution_op4 = "EXECUTION_OP4";
    Base::execution_op4_after_relative = "EXECUTION_OP4_AFTER_RELATIVE";
    Base::execution_pc = "EXECUTION_PC";
    Base::execution_rop1 = "EXECUTION_ROP1";
    Base::execution_rop2 = "EXECUTION_ROP2";
    Base::execution_rop3 = "EXECUTION_ROP3";
    Base::execution_rop4 = "EXECUTION_ROP4";
    Base::execution_sel = "EXECUTION_SEL";
    Base::execution_sel_addressing_error = "EXECUTION_SEL_ADDRESSING_ERROR";
    Base::execution_sel_op1_is_address = "EXECUTION_SEL_OP1_IS_ADDRESS";
    Base::execution_sel_op2_is_address = "EXECUTION_SEL_OP2_IS_ADDRESS";
    Base::execution_sel_op3_is_address = "EXECUTION_SEL_OP3_IS_ADDRESS";
    Base::execution_sel_op4_is_address = "EXECUTION_SEL_OP4_IS_ADDRESS";
    Base::perm_dummy_dynamic_inv = "PERM_DUMMY_DYNAMIC_INV";
    Base::lookup_dummy_precomputed_inv = "LOOKUP_DUMMY_PRECOMPUTED_INV";
    Base::lookup_dummy_dynamic_inv = "LOOKUP_DUMMY_DYNAMIC_INV";
    Base::lookup_dummy_precomputed_counts = "LOOKUP_DUMMY_PRECOMPUTED_COUNTS";
    Base::lookup_dummy_dynamic_counts = "LOOKUP_DUMMY_DYNAMIC_COUNTS";
};

void AvmFlavor::Transcript::deserialize_full_transcript()
{
    size_t num_frs_read = 0;
    circuit_size = deserialize_from_buffer<uint32_t>(proof_data, num_frs_read);

    for (auto& commitment : commitments) {
        commitment = deserialize_from_buffer<Commitment>(proof_data, num_frs_read);
    }

    for (size_t i = 0; i < CONST_PROOF_SIZE_LOG_N; ++i) {
        sumcheck_univariates.emplace_back(deserialize_from_buffer<bb::Univariate<FF, BATCHED_RELATION_PARTIAL_LENGTH>>(
            Transcript::proof_data, num_frs_read));
    }

    sumcheck_evaluations =
        deserialize_from_buffer<std::array<FF, NUM_ALL_ENTITIES>>(Transcript::proof_data, num_frs_read);

    for (size_t i = 0; i < CONST_PROOF_SIZE_LOG_N - 1; ++i) {
        gemini_fold_comms.push_back(deserialize_from_buffer<Commitment>(proof_data, num_frs_read));
    }

    for (size_t i = 0; i < CONST_PROOF_SIZE_LOG_N; ++i) {
        gemini_fold_evals.push_back(deserialize_from_buffer<FF>(proof_data, num_frs_read));
    }

    shplonk_q_comm = deserialize_from_buffer<Commitment>(proof_data, num_frs_read);

    kzg_w_comm = deserialize_from_buffer<Commitment>(proof_data, num_frs_read);
}

void AvmFlavor::Transcript::serialize_full_transcript()
{
    size_t old_proof_length = proof_data.size();
    Transcript::proof_data.clear();

    serialize_to_buffer(circuit_size, Transcript::proof_data);

    for (const auto& commitment : commitments) {
        serialize_to_buffer(commitment, Transcript::proof_data);
    }

    for (size_t i = 0; i < CONST_PROOF_SIZE_LOG_N; ++i) {
        serialize_to_buffer(sumcheck_univariates[i], Transcript::proof_data);
    }

    serialize_to_buffer(sumcheck_evaluations, Transcript::proof_data);

    for (size_t i = 0; i < CONST_PROOF_SIZE_LOG_N - 1; ++i) {
        serialize_to_buffer(gemini_fold_comms[i], proof_data);
    }

    for (size_t i = 0; i < CONST_PROOF_SIZE_LOG_N; ++i) {
        serialize_to_buffer(gemini_fold_evals[i], proof_data);
    }

    serialize_to_buffer(shplonk_q_comm, proof_data);
    serialize_to_buffer(kzg_w_comm, proof_data);

    // sanity check to make sure we generate the same length of proof as before.
    ASSERT(proof_data.size() == old_proof_length);
}

AvmFlavor::PartiallyEvaluatedMultivariates::PartiallyEvaluatedMultivariates(const size_t circuit_size)
{
    // Storage is only needed after the first partial evaluation, hence polynomials of size (n / 2)
    for (auto& poly : get_all()) {
        poly = Polynomial(circuit_size / 2);
    }
}

AvmFlavor::ProvingKey::ProvingKey(const size_t circuit_size, const size_t num_public_inputs)
    : circuit_size(circuit_size)
    , evaluation_domain(bb::EvaluationDomain<FF>(circuit_size, circuit_size))
    , commitment_key(std::make_shared<CommitmentKey>(circuit_size + 1))
{
    // TODO: These come from PrecomputedEntitiesBase, ideal we'd just call that class's constructor.
    this->log_circuit_size = numeric::get_msb(circuit_size);
    this->num_public_inputs = num_public_inputs;

    // The proving key's polynomials are not allocated here because they are later overwritten
    // AvmComposer::compute_witness(). We should probably refactor this flow.
};

/**
 * @brief Serialize verification key to field elements
 *
 * @return std::vector<FF>
 */
std::vector<AvmFlavor::VerificationKey::FF> AvmFlavor::VerificationKey::to_field_elements() const
{
    std::vector<FF> elements = { FF(circuit_size), FF(num_public_inputs) };

    for (auto const& comm : get_all()) {
        std::vector<FF> comm_as_fields = field_conversion::convert_to_bn254_frs(comm);
        elements.insert(elements.end(), comm_as_fields.begin(), comm_as_fields.end());
    }
    return elements;
}

} // namespace bb::avm2