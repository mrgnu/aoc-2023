#pragma once

#include "utils.hh"

namespace day_9 {

using value_t = long;
using timeline_t = std::vector<value_t>;
using input_t = std::vector<timeline_t>;

using result_t = long;

input_t parse_input(const utils::lines_t& lines);

}  // namespace day_9
