#pragma once

#include "utils.hh"

namespace day_10 {

using dimen_t = int;
using coord_t = std::pair<dimen_t, dimen_t>;
using tile_t = utils::line_t::value_type;
using map_t = std::map<coord_t, tile_t>;

map_t parse_map(const utils::lines_t& lines);

}  // namespace day_10
