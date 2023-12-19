#pragma once

#include <set>

#include "utils.hh"

namespace day_11 {

using dimen_t = unsigned;
using coord_t = std::pair<dimen_t, dimen_t>;
using galaxies_t = std::set<coord_t>;

galaxies_t parse_map(const utils::lines_t& lines);

}  // namespace day_11
