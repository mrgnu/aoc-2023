#pragma once

#include <set>

#include "utils.hh"

namespace day_11 {

using dimen_t = long;
using coord_t = std::pair<dimen_t, dimen_t>;
using galaxies_t = std::set<coord_t>;

galaxies_t parse_map(const utils::lines_t& lines, const dimen_t exp_rate = 1);

dimen_t part_1(const utils::lines_t& lines);
dimen_t part_2(const utils::lines_t& lines,
               const dimen_t exp_rate = 1000000 - 1);

}  // namespace day_11
