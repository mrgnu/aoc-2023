#pragma once

#include "utils.hh"

namespace day_12 {

using num_t = unsigned;
using nums_t = std::vector<num_t>;
using arr_count_t = unsigned long;

bool is_valid(const utils::line_t& l, const nums_t& nums);

arr_count_t part_1(const utils::lines_t& lines);
arr_count_t part_2(const utils::lines_t& lines);

}  // namespace day_12
