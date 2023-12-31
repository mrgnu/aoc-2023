#pragma once

#include "utils.hh"

namespace day_10 {

enum dir_t {
  // NOTE: code assumes vertical dirs come before horizontal
  UP,
  DOWN,
  LEFT,
  RIGHT,
};

using dimen_t = int;
using coord_t = std::pair<dimen_t, dimen_t>;
using tile_t = utils::line_t::value_type;
using map_t = std::map<coord_t, tile_t>;
using dist_t = unsigned;

// start coord and map, where map has had 'S' replaced with actual start tile
using input_t = std::pair<coord_t, map_t>;

map_t parse_map(const utils::lines_t& lines);
input_t parse_input(const utils::lines_t& lines);
std::pair<coord_t, tile_t> find_start_tile(const map_t& map);

dist_t part_1(const utils::lines_t& lines);
size_t part_2(const utils::lines_t& lines);

}  // namespace day_10
