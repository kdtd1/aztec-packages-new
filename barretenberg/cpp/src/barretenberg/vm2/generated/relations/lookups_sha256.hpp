// AUTOGENERATED FILE
#pragma once

#include "../columns.hpp"
#include "barretenberg/relations/generic_lookup/generic_lookup_relation.hpp"

#include <cstddef>
#include <string_view>
#include <tuple>

namespace bb::avm2 {

/////////////////// lookup_sha256_round_constant ///////////////////

class lookup_sha256_round_constant_lookup_settings {
  public:
    static constexpr std::string_view NAME = "LOOKUP_SHA256_ROUND_CONSTANT";
    static constexpr std::string_view RELATION_NAME = "sha256";

    static constexpr size_t READ_TERMS = 1;
    static constexpr size_t WRITE_TERMS = 1;
    static constexpr size_t READ_TERM_TYPES[READ_TERMS] = { 0 };
    static constexpr size_t WRITE_TERM_TYPES[WRITE_TERMS] = { 0 };
    static constexpr size_t LOOKUP_TUPLE_SIZE = 2;
    static constexpr size_t INVERSE_EXISTS_POLYNOMIAL_DEGREE = 4;
    static constexpr size_t READ_TERM_DEGREE = 0;
    static constexpr size_t WRITE_TERM_DEGREE = 0;

    // Columns using the Column enum.
    static constexpr Column SRC_SELECTOR = Column::sha256_sel;
    static constexpr Column DST_SELECTOR = Column::precomputed_sel_sha256_compression;
    static constexpr Column COUNTS = Column::lookup_sha256_round_constant_counts;
    static constexpr Column INVERSES = Column::lookup_sha256_round_constant_inv;
    static constexpr std::array<Column, LOOKUP_TUPLE_SIZE> SRC_COLUMNS = { Column::sha256_round_count,
                                                                           Column::sha256_round_constant };
    static constexpr std::array<Column, LOOKUP_TUPLE_SIZE> DST_COLUMNS = {
        Column::precomputed_clk, Column::precomputed_sha256_compression_round_constant
    };

    template <typename AllEntities> static inline auto inverse_polynomial_is_computed_at_row(const AllEntities& in)
    {
        return (in._sha256_sel() == 1 || in._precomputed_sel_sha256_compression() == 1);
    }

    template <typename Accumulator, typename AllEntities>
    static inline auto compute_inverse_exists(const AllEntities& in)
    {
        using View = typename Accumulator::View;
        const auto is_operation = View(in._sha256_sel());
        const auto is_table_entry = View(in._precomputed_sel_sha256_compression());
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
        return std::forward_as_tuple(in._lookup_sha256_round_constant_inv(),
                                     in._lookup_sha256_round_constant_counts(),
                                     in._sha256_sel(),
                                     in._precomputed_sel_sha256_compression(),
                                     in._sha256_round_count(),
                                     in._sha256_round_constant(),
                                     in._precomputed_clk(),
                                     in._precomputed_sha256_compression_round_constant());
    }
};

template <typename FF_>
class lookup_sha256_round_constant_relation
    : public GenericLookupRelation<lookup_sha256_round_constant_lookup_settings, FF_> {
  public:
    using Settings = lookup_sha256_round_constant_lookup_settings;
    static constexpr std::string_view NAME = lookup_sha256_round_constant_lookup_settings::NAME;
    static constexpr std::string_view RELATION_NAME = lookup_sha256_round_constant_lookup_settings::RELATION_NAME;

    template <typename AllEntities> inline static bool skip(const AllEntities& in)
    {
        return in.lookup_sha256_round_constant_inv.is_zero();
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
