#pragma once

#include "utils.hh"

namespace day_10 {

enum dir_t {
  LEFT,
  UP,
  RIGHT,
  DOWN,
};

using dimen_t = int;
using coord_t = std::pair<dimen_t, dimen_t>;
using tile_t = utils::line_t::value_type;
using map_t = std::map<coord_t, tile_t>;

map_t parse_map(const utils::lines_t& lines);
std::pair<coord_t, tile_t> find_start_tile(const map_t& map);

}  // namespace day_10
