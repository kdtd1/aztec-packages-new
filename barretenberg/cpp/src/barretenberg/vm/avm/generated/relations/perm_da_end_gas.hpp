// AUTOGENERATED FILE
#pragma once

#include "barretenberg/relations/generic_permutation/generic_permutation_relation.hpp"

#include <cstddef>
#include <tuple>

namespace bb {

class perm_da_end_gas_permutation_settings {
  public:
    // This constant defines how many columns are bundled together to form each set.
    constexpr static size_t COLUMNS_PER_SET = 1;

    template <typename AllEntities> static inline auto inverse_polynomial_is_computed_at_row(const AllEntities& in)
    {
        return (in.main_sel_execution_end == 1 || in.main_sel_da_end_gas_kernel_input == 1);
    }

    template <typename AllEntities> static inline auto get_const_entities(const AllEntities& in)
    {
        return std::forward_as_tuple(in.perm_da_end_gas_inv,
                                     in.main_sel_execution_end,
                                     in.main_sel_execution_end,
                                     in.main_sel_da_end_gas_kernel_input,
                                     in.main_da_gas_remaining,
                                     in.main_kernel_inputs);
    }

    template <typename AllEntities> static inline auto get_nonconst_entities(AllEntities& in)
    {
        return std::forward_as_tuple(in.perm_da_end_gas_inv,
                                     in.main_sel_execution_end,
                                     in.main_sel_execution_end,
                                     in.main_sel_da_end_gas_kernel_input,
                                     in.main_da_gas_remaining,
                                     in.main_kernel_inputs);
    }
};

template <typename FF_>
class perm_da_end_gas_relation : public GenericPermutationRelation<perm_da_end_gas_permutation_settings, FF_> {
  public:
    static constexpr const char* NAME = "PERM_DA_END_GAS";
};
template <typename FF_> using perm_da_end_gas = GenericPermutation<perm_da_end_gas_permutation_settings, FF_>;

} // namespace bb