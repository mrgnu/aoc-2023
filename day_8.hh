#pragma once

#include "utils.hh"

namespace day_8 {

using directions_t = std::string;
using direction_t = directions_t::value_type;
using coord_t = std::string;
using coords_t = std::pair<coord_t, coord_t>;
using map_t = std::map<coord_t, coords_t>;

using input_t = std::pair<directions_t, map_t>;

using result_t = size_t;

input_t parse_lines(const utils::lines_t& lines);

result_t part_1(const utils::lines_t& lines);

}  // namespace day_8
