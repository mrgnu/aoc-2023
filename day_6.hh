#pragma once

#include "utils.hh"

namespace day_6 {

const utils::lines_t example_lines{
    "Time:      7  15   30",
    "Distance:  9  40  200",
};

using time_t = long;
using dist_t = long;

using race_t = std::pair<time_t, dist_t>;
using races_t = std::vector<race_t>;

races_t parse_lines(const utils::lines_t& lines);

using result_t = long;

}  // namespace day_6
