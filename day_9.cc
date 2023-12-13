#include "day_9.hh"

#include <ranges>

using namespace std;
using namespace utils;

namespace {

using namespace day_9;

timeline_t parse_line(const line_t& line) {
  const parts_t parts = split_string(line, regex("[[:blank:]]+"));
  auto nums = parts | views::transform([](const part_t& part) -> long {
                return stol(part);
              });
  return timeline_t(nums.begin(), nums.end());
}

}  // namespace

namespace day_9 {

input_t parse_input(const lines_t& lines) {
  auto timelines = lines | views::transform(parse_line);
  return input_t(timelines.begin(), timelines.end());
}

}  // namespace day_9
