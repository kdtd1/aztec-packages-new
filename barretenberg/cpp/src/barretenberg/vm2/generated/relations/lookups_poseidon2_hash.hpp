// AUTOGENERATED FILE
#pragma once

#include "../columns.hpp"
#include "barretenberg/relations/generic_lookup/generic_lookup_relation.hpp"

#include <cstddef>
#include <string_view>
#include <tuple>

namespace bb::avm2 {

/////////////////// lookup_pos2_perm ///////////////////

class lookup_pos2_perm_lookup_settings {
  public:
    static constexpr std::string_view NAME = "LOOKUP_POS2_PERM";
    static constexpr std::string_view RELATION_NAME = "poseidon2_hash";

    static constexpr size_t READ_TERMS = 1;
    static constexpr size_t WRITE_TERMS = 1;
    static constexpr size_t READ_TERM_TYPES[READ_TERMS] = { 0 };
    static constexpr size_t WRITE_TERM_TYPES[WRITE_TERMS] = { 0 };
    static constexpr size_t LOOKUP_TUPLE_SIZE = 8;
    static constexpr size_t INVERSE_EXISTS_POLYNOMIAL_DEGREE = 4;
    static constexpr size_t READ_TERM_DEGREE = 0;
    static constexpr size_t WRITE_TERM_DEGREE = 0;

    // Columns using the Column enum.
    static constexpr Column SRC_SELECTOR = Column::poseidon2_hash_sel;
    static constexpr Column DST_SELECTOR = Column::poseidon2_perm_sel;
    static constexpr Column COUNTS = Column::lookup_pos2_perm_counts;
    static constexpr Column INVERSES = Column::lookup_pos2_perm_inv;
    static constexpr std::array<Column, LOOKUP_TUPLE_SIZE> SRC_COLUMNS = {
        Column::poseidon2_hash_a_0, Column::poseidon2_hash_a_1, Column::poseidon2_hash_a_2, Column::poseidon2_hash_a_3,
        Column::poseidon2_hash_b_0, Column::poseidon2_hash_b_1, Column::poseidon2_hash_b_2, Column::poseidon2_hash_b_3
    };
    static constexpr std::array<Column, LOOKUP_TUPLE_SIZE> DST_COLUMNS = {
        Column::poseidon2_perm_a_0, Column::poseidon2_perm_a_1, Column::poseidon2_perm_a_2, Column::poseidon2_perm_a_3,
        Column::poseidon2_perm_b_0, Column::poseidon2_perm_b_1, Column::poseidon2_perm_b_2, Column::poseidon2_perm_b_3
    };

    template <typename AllEntities> static inline auto inverse_polynomial_is_computed_at_row(const AllEntities& in)
    {
        return (in._poseidon2_hash_sel() == 1 || in._poseidon2_perm_sel() == 1);
    }

    template <typename Accumulator, typename AllEntities>
    static inline auto compute_inverse_exists(const AllEntities& in)
    {
        using View = typename Accumulator::View;
        const auto is_operation = View(in._poseidon2_hash_sel());
        const auto is_table_entry = View(in._poseidon2_perm_sel());
        return (is_operation + is_table_entry - is_operation * is_table_entry);
    }

    template <typename AllEntities> static inline auto get_const_entities(const AllEntities& in)
    {
        return get_entities(in);
    }

    template <typename AllEntities> static inline auto get_nonconst_entities(AllEntities& in)
    {
        return get_entities(in);
    }

    template <typename AllEntities> static inline auto get_entities(AllEntities&& in)
    {
        return std::forward_as_tuple(in._lookup_pos2_perm_inv(),
                                     in._lookup_pos2_perm_counts(),
                                     in._poseidon2_hash_sel(),
                                     in._poseidon2_perm_sel(),
                                     in._poseidon2_hash_a_0(),
                                     in._poseidon2_hash_a_1(),
                                     in._poseidon2_hash_a_2(),
                                     in._poseidon2_hash_a_3(),
                                     in._poseidon2_hash_b_0(),
                                     in._poseidon2_hash_b_1(),
                                     in._poseidon2_hash_b_2(),
                                     in._poseidon2_hash_b_3(),
                                     in._poseidon2_perm_a_0(),
                                     in._poseidon2_perm_a_1(),
                                     in._poseidon2_perm_a_2(),
                                     in._poseidon2_perm_a_3(),
                                     in._poseidon2_perm_b_0(),
                                     in._poseidon2_perm_b_1(),
                                     in._poseidon2_perm_b_2(),
                                     in._poseidon2_perm_b_3());
    }
};

template <typename FF_>
class lookup_pos2_perm_relation : public GenericLookupRelation<lookup_pos2_perm_lookup_settings, FF_> {
  public:
    using Settings = lookup_pos2_perm_lookup_settings;
    static constexpr std::string_view NAME = lookup_pos2_perm_lookup_settings::NAME;
    static constexpr std::string_view RELATION_NAME = lookup_pos2_perm_lookup_settings::RELATION_NAME;

    template <typename AllEntities> inline static bool skip(const AllEntities& in)
    {
        return in.lookup_pos2_perm_inv.is_zero();
    }

    static std::string get_subrelation_label(size_t index)
    {
        if (index == 0) {
            return "INVERSES_ARE_CORRECT";
        } else if (index == 1) {
            return "ACCUMULATION_IS_CORRECT";
        }
        return std::to_string(index);
    }
};

} // namespace bb::avm2
