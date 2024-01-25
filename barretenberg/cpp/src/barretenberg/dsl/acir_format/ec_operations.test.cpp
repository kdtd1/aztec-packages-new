#include "ec_operations.hpp"
#include "acir_format.hpp"
#include "barretenberg/plonk/proof_system/types/proof.hpp"
#include "barretenberg/plonk/proof_system/verification_key/verification_key.hpp"

#include <gtest/gtest.h>
#include <vector>

namespace acir_format::tests {
using curve_ct = bb::stdlib::secp256k1<Builder>;

class EcOperations : public ::testing::Test {
  protected:
    static void SetUpTestSuite() { bb::srs::init_crs_factory("../srs_db/ignition"); }
};

size_t generate_ec_add_constraint(EcAdd& ec_add_constraint, WitnessVector& witness_values)
{
    using cycle_group_ct = bb::stdlib::cycle_group<Builder>;
    witness_values.push_back(0);
    auto g1 = grumpkin::g1::affine_one;
    cycle_group_ct input_point(g1);
    // Doubling
    cycle_group_ct result = input_point.dbl();
    // add: x,y,x2,y2
    witness_values.push_back(g1.x);
    witness_values.push_back(g1.y);
    witness_values.push_back(g1.x);
    witness_values.push_back(g1.y);
    witness_values.push_back(result.x.get_value());
    witness_values.push_back(result.y.get_value());
    ec_add_constraint = EcAdd{
        .input1_x = 1,
        .input1_y = 2,
        .input2_x = 3,
        .input2_y = 4,
        .result_x = 5,
        .result_y = 6,
    };
    return witness_values.size();
}

size_t generate_ec_double_constraint(EcDouble& ec_double_constraint, WitnessVector& witness_values)
{

    using cycle_group_ct = bb::stdlib::cycle_group<Builder>;
    auto g1 = grumpkin::g1::affine_one;
    cycle_group_ct input_point(g1);
    // Doubling
    cycle_group_ct result = input_point.dbl();
    // add: x,y,x2,y2
    uint32_t result_x_witness_index = static_cast<uint32_t>(witness_values.size());

    witness_values.push_back(result.x.get_value());
    uint32_t result_y_witness_index = static_cast<uint32_t>(witness_values.size());
    witness_values.push_back(result.y.get_value());
    ec_double_constraint = EcDouble{
        .input_x = 1,
        .input_y = 2,
        .result_x = result_x_witness_index,
        .result_y = result_y_witness_index,
    };
    return witness_values.size();
}

TEST_F(EcOperations, TestECOperations)
{
    EcAdd ec_add_constraint;
    EcDouble ec_double_constraint;

    WitnessVector witness_values;
    generate_ec_add_constraint(ec_add_constraint, witness_values);
    size_t num_variables = generate_ec_double_constraint(ec_double_constraint, witness_values);

    poly_triple constrain_5_is_7{
        .a = 5,
        .b = 7,
        .c = 0,
        .q_m = 0,
        .q_l = 1,
        .q_r = -1,
        .q_o = 0,
        .q_c = 0,
    };
    poly_triple constrain_6_is_8{
        .a = 6,
        .b = 8,
        .c = 0,
        .q_m = 0,
        .q_l = 1,
        .q_r = -1,
        .q_o = 0,
        .q_c = 0,
    };

    AcirFormat constraint_system{
        .varnum = static_cast<uint32_t>(num_variables + 1),
        .public_inputs = {},
        .logic_constraints = {},
        .range_constraints = {},
        .sha256_constraints = {},
        .schnorr_constraints = {},
        .ecdsa_k1_constraints = {},
        .ecdsa_r1_constraints = {},
        .blake2s_constraints = {},
        .blake3_constraints = {},
        .keccak_constraints = {},
        .keccak_var_constraints = {},
        .keccak_permutations = {},
        .pedersen_constraints = {},
        .pedersen_hash_constraints = {},
        .fixed_base_scalar_mul_constraints = {},
        .ec_add_constraints = { ec_add_constraint },
        .ec_double_constraints = { ec_double_constraint },
        .recursion_constraints = {},
        .bigint_from_le_bytes_constraints = {},
        .bigint_operations = {},
        .constraints = { constrain_5_is_7, constrain_6_is_8 },
        .block_constraints = {},
    };

    auto builder = create_circuit(constraint_system, /*size_hint*/ 0, witness_values);

    auto composer = Composer();
    auto prover = composer.create_prover(builder);

    auto proof = prover.construct_proof();
    EXPECT_TRUE(builder.check_circuit());
    auto verifier = composer.create_verifier(builder);
    EXPECT_EQ(verifier.verify_proof(proof), true);
}

} // namespace acir_format::tests
