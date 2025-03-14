#pragma once

#include "barretenberg/eccvm/eccvm_circuit_builder.hpp"
#include "barretenberg/eccvm/eccvm_prover.hpp"
#include "barretenberg/eccvm/eccvm_trace_checker.hpp"
#include "barretenberg/eccvm/eccvm_verifier.hpp"
#include "barretenberg/goblin/mock_circuits.hpp"
#include "barretenberg/goblin/types.hpp"
#include "barretenberg/plonk_honk_shared/proving_key_inspector.hpp"
#include "barretenberg/polynomials/polynomial.hpp"
#include "barretenberg/stdlib/goblin_verifier/merge_recursive_verifier.hpp"
#include "barretenberg/stdlib_circuit_builders/mega_circuit_builder.hpp"
#include "barretenberg/stdlib_circuit_builders/mega_flavor.hpp"
#include "barretenberg/translator_vm/translator_circuit_builder.hpp"
#include "barretenberg/translator_vm/translator_prover.hpp"
#include "barretenberg/translator_vm/translator_verifier.hpp"
#include "barretenberg/ultra_honk/merge_prover.hpp"
#include "barretenberg/ultra_honk/merge_verifier.hpp"
#include "barretenberg/ultra_honk/ultra_prover.hpp"
#include "barretenberg/ultra_honk/ultra_verifier.hpp"

namespace bb {

class GoblinProver {
    using Commitment = MegaFlavor::Commitment;
    using FF = MegaFlavor::FF;

  public:
    using MegaBuilder = MegaCircuitBuilder;
    using Fr = bb::fr;
    using Transcript = NativeTranscript;
    using MegaDeciderProvingKey = DeciderProvingKey_<MegaFlavor>;
    using OpQueue = ECCOpQueue;
    using ECCVMBuilder = ECCVMFlavor::CircuitBuilder;
    using ECCVMProvingKey = ECCVMFlavor::ProvingKey;
    using TranslationEvaluations = ECCVMProver::TranslationEvaluations;
    using TranslatorBuilder = TranslatorCircuitBuilder;
    using RecursiveMergeVerifier = stdlib::recursion::goblin::MergeRecursiveVerifier_<MegaBuilder>;
    using PairingPoints = RecursiveMergeVerifier::PairingPoints;
    using MergeProver = MergeProver_<MegaFlavor>;
    using VerificationKey = MegaFlavor::VerificationKey;
    using MergeProof = std::vector<FF>;
    /**
     * @brief Output of goblin::accumulate; an Ultra proof and the corresponding verification key
     *
     */

    std::shared_ptr<OpQueue> op_queue = std::make_shared<OpQueue>();
    std::shared_ptr<CommitmentKey<curve::BN254>> commitment_key;

    MergeProof merge_proof;
    GoblinProof goblin_proof;

    // on the first call to accumulate there is no merge proof to verify
    bool merge_proof_exists{ false };

    std::shared_ptr<ECCVMProvingKey> get_eccvm_proving_key() const { return eccvm_key; }
    std::shared_ptr<TranslatorProvingKey::ProvingKey> get_translator_proving_key() const
    {
        return translator_key->proving_key;
    }

  private:
    // TODO(https://github.com/AztecProtocol/barretenberg/issues/798) unique_ptr use is a hack
    std::unique_ptr<TranslatorProver> translator_prover;
    std::unique_ptr<ECCVMProver> eccvm_prover;
    std::shared_ptr<ECCVMProvingKey> eccvm_key;
    std::shared_ptr<TranslatorProvingKey> translator_key;

    GoblinAccumulationOutput accumulator; // Used only for ACIR methods for now

  public:
    GoblinProver(const std::shared_ptr<CommitmentKey<curve::BN254>>& bn254_commitment_key = nullptr)
    { // Mocks the interaction of a first circuit with the op queue due to the inability to currently handle zero
      // commitments (https://github.com/AztecProtocol/barretenberg/issues/871) which would otherwise appear in the
      // first round of the merge protocol. To be removed once the issue has been resolved.
        commitment_key = bn254_commitment_key ? bn254_commitment_key : nullptr;
        GoblinMockCircuits::perform_op_queue_interactions_for_mock_first_circuit(op_queue);
    }
    /**
     * @brief Construct a MegaHonk proof and a merge proof for the present circuit.
     * @details If there is a previous merge proof, recursively verify it.
     *
     * @param circuit_builder
     */
    GoblinAccumulationOutput accumulate(MegaBuilder& circuit_builder)
    {
        // Complete the circuit logic by recursively verifying previous merge proof if it exists
        if (merge_proof_exists) {
            RecursiveMergeVerifier merge_verifier{ &circuit_builder };
            [[maybe_unused]] auto pairing_points = merge_verifier.verify_proof(merge_proof);
        }

        // Construct a Honk proof for the main circuit
        auto proving_key = std::make_shared<MegaDeciderProvingKey>(circuit_builder);
        MegaProver prover(proving_key);
        auto ultra_proof = prover.construct_proof();
        auto verification_key = std::make_shared<VerificationKey>(proving_key->proving_key);

        // Construct and store the merge proof to be recursively verified on the next call to accumulate
        MergeProver merge_prover{ circuit_builder.op_queue };
        merge_proof = merge_prover.construct_proof();

        if (!merge_proof_exists) {
            merge_proof_exists = true;
        }

        return { ultra_proof, verification_key };
    };

    /**
     * @brief Add a recursive merge verifier to input circuit and construct a merge proof for the updated op queue
     * @details When this method is used, the "prover" functionality of the IVC scheme must be performed explicitly, but
     * this method has to be called first so that the recursive merge verifier can be "appended" to the circuit being
     * accumulated
     *
     * @param circuit_builder
     */
    void merge(MegaBuilder& circuit_builder)
    {
        // Append a recursive merge verification of the merge proof
        if (merge_proof_exists) {
            [[maybe_unused]] auto pairing_points = verify_merge(circuit_builder, merge_proof);
        }

        // Construct a merge proof for the present circuit
        merge_proof = prove_merge(circuit_builder);
    };

    /**
     * @brief Append recursive verification of a merge proof to a provided circuit
     *
     * @param circuit_builder
     * @return PairingPoints
     */
    PairingPoints verify_merge(MegaBuilder& circuit_builder, MergeProof& proof) const
    {
        PROFILE_THIS_NAME("Goblin::merge");
        RecursiveMergeVerifier merge_verifier{ &circuit_builder };
        return merge_verifier.verify_proof(proof);
    };

    /**
     * @brief Construct a merge proof for the goblin ECC ops in the provided circuit
     *
     * @param circuit_builder
     */
    MergeProof prove_merge(MegaBuilder& circuit_builder)
    {
        PROFILE_THIS_NAME("Goblin::merge");
        // TODO(https://github.com/AztecProtocol/barretenberg/issues/993): Some circuits (particularly on the first call
        // to accumulate) may not have any goblin ecc ops prior to the call to merge(), so the commitment to the new
        // contribution (C_t_shift) in the merge prover will be the point at infinity. (Note: Some dummy ops are added
        // in 'add_gates_to_ensure...' but not until proving_key construction which comes later). See issue for ideas
        // about how to resolve.
        if (circuit_builder.blocks.ecc_op.size() == 0) {
            MockCircuits::construct_goblin_ecc_op_circuit(circuit_builder); // Add some arbitrary goblin ECC ops
        }

        if (!merge_proof_exists) {
            merge_proof_exists = true;
        }

        MergeProver merge_prover{ circuit_builder.op_queue, commitment_key };
        return merge_prover.construct_proof();
    };

    /**
     * @brief Construct an ECCVM proof and the translation polynomial evaluations
     *
     */
    void prove_eccvm()
    {
        {

            PROFILE_THIS_NAME("Create ECCVMBuilder and ECCVMProver");

            auto eccvm_builder = std::make_unique<ECCVMBuilder>(op_queue);
            // As is it used in ClientIVC, we make it fixed size = 2^{CONST_ECCVM_LOG_N}
            eccvm_prover = std::make_unique<ECCVMProver>(*eccvm_builder, /*fixed_size =*/true);
        }
        {

            PROFILE_THIS_NAME("Construct ECCVM Proof");

            goblin_proof.eccvm_proof = eccvm_prover->construct_proof();
        }

        {

            PROFILE_THIS_NAME("Assign Translation Evaluations");

            goblin_proof.translation_evaluations = eccvm_prover->translation_evaluations;
        }
    }

    /**
     * @brief Construct a translator proof
     *
     */
    void prove_translator()
    {
        fq translation_batching_challenge_v = eccvm_prover->batching_challenge_v;
        fq evaluation_challenge_x = eccvm_prover->evaluation_challenge_x;
        std::shared_ptr<Transcript> transcript = eccvm_prover->transcript;
        eccvm_key = eccvm_prover->key;
        eccvm_prover = nullptr;
        {

            PROFILE_THIS_NAME("Create TranslatorBuilder and TranslatorProver");

            auto translator_builder =
                std::make_unique<TranslatorBuilder>(translation_batching_challenge_v, evaluation_challenge_x, op_queue);
            translator_key = std::make_shared<TranslatorProvingKey>(*translator_builder, commitment_key);
            translator_prover = std::make_unique<TranslatorProver>(translator_key, transcript);
        }

        {

            PROFILE_THIS_NAME("Construct Translator Proof");

            goblin_proof.translator_proof = translator_prover->construct_proof();
        }
    }

    /**
     * @brief Constuct a full Goblin proof (ECCVM, Translator, merge)
     * @details The merge proof is assumed to already have been constucted in the last accumulate step. It is simply
     * moved into the final proof here.
     *
     * @return Proof
     */
    GoblinProof prove(MergeProof merge_proof_in = {})
    {

        PROFILE_THIS_NAME("Goblin::prove");

        goblin_proof.merge_proof = merge_proof_in.empty() ? std::move(merge_proof) : std::move(merge_proof_in);
        {
            PROFILE_THIS_NAME("prove_eccvm");
            vinfo("prove eccvm...");
            prove_eccvm();
            vinfo("finished eccvm proving.");
        }
        {
            PROFILE_THIS_NAME("prove_translator");
            vinfo("prove translator...");
            prove_translator();
            vinfo("finished translator proving.");
        }
        return goblin_proof;
    };
};

class GoblinVerifier {
  public:
    using ECCVMVerificationKey = ECCVMFlavor::VerificationKey;
    using TranslatorVerificationKey = bb::TranslatorFlavor::VerificationKey;
    using MergeVerifier = bb::MergeVerifier_<MegaFlavor>;

    struct VerifierInput {
        std::shared_ptr<ECCVMVerificationKey> eccvm_verification_key;
        std::shared_ptr<TranslatorVerificationKey> translator_verification_key;
    };

  private:
    std::shared_ptr<ECCVMVerificationKey> eccvm_verification_key;
    std::shared_ptr<TranslatorVerificationKey> translator_verification_key;

  public:
    GoblinVerifier(std::shared_ptr<ECCVMVerificationKey> eccvm_verification_key,
                   std::shared_ptr<TranslatorVerificationKey> translator_verification_key)
        : eccvm_verification_key(eccvm_verification_key)
        , translator_verification_key(translator_verification_key)
    {}

    GoblinVerifier(VerifierInput input)
        : eccvm_verification_key(input.eccvm_verification_key)
        , translator_verification_key(input.translator_verification_key)
    {}

    /**
     * @brief Verify a full Goblin proof (ECCVM, Translator, merge)
     *
     * @param proof
     * @return true
     * @return false
     */
    bool verify(const GoblinProof& proof)
    {
        MergeVerifier merge_verifier;
        bool merge_verified = merge_verifier.verify_proof(proof.merge_proof);

        ECCVMVerifier eccvm_verifier(eccvm_verification_key);
        bool eccvm_verified = eccvm_verifier.verify_proof(proof.eccvm_proof);

        TranslatorVerifier translator_verifier(translator_verification_key, eccvm_verifier.transcript);

        bool accumulator_construction_verified = translator_verifier.verify_proof(
            proof.translator_proof, eccvm_verifier.evaluation_challenge_x, eccvm_verifier.batching_challenge_v);
        // TODO(https://github.com/AztecProtocol/barretenberg/issues/799): Ensure translation_evaluations are passed
        // correctly
        bool translation_verified = translator_verifier.verify_translation(
            proof.translation_evaluations, eccvm_verifier.translation_masking_term_eval);

        vinfo("merge verified?: ", merge_verified);
        vinfo("eccvm verified?: ", eccvm_verified);
        vinfo("accumulator construction_verified?: ", accumulator_construction_verified);
        vinfo("translation verified?: ", translation_verified);

        return merge_verified && eccvm_verified && accumulator_construction_verified && translation_verified;
    };
};
} // namespace bb
