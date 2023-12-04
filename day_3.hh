#pragma once

#include <map>
#include <set>
#include <string>
#include <variant>

#include "utils.hh"

namespace day_3 {

// clang-format off
const utils::lines_t example_lines{
  // 0123456789
    "467..114..", // 0
    "...*......", // 1
    "..35..633.", // 2
    "......#...", // 3
    "617*......", // 4
    ".....+.58.", // 5
    "..592.....", // 6
    "......755.", // 7
    "...$.*....", // 8
    ".664.598..", // 9
};
// clang-format on

using result_t = long;

using dim_t = int;
using coord_t = std::pair<dim_t, dim_t>;
using coords_t = std::set<coord_t>;

// NOTE: part numbers may span several tiles. right is coord of leftmost coord
// of part number, to allow filtering out dups.
using part_num_t = std::pair<result_t, coord_t>;
using part_nums_t = std::vector<part_num_t>;

using part_t = utils::line_t::value_type;

using val_t = std::variant<part_num_t, part_t>;

using schematic_t = std::map<coord_t, val_t>;

schematic_t parse_schematic(const utils::lines_t& lines);

part_nums_t part_nums(const schematic_t& schematic);

result_t part_1(const utils::lines_t& lines);
result_t part_2(const utils::lines_t& lines);

}  // namespace day_3
