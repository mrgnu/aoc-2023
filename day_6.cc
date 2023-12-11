#include "day_6.hh"

#include <cmath>
#include <format>
#include <numeric>
#include <ranges>

using namespace std;
using namespace utils;

namespace {

using namespace day_6;

vector<long> read_vals(const line_t& line) {
  const parts_t parts = split_string(line, regex("[[:blank:]]+"));
  vector<long> vals;
  vals.reserve(parts.size());
  for (const part_t& part : parts) {
    vals.push_back(stol(part));
  }
  return vals;
}

}  // namespace

namespace day_6 {

races_t parse_lines(const lines_t& lines) {
  if (lines.size() != 2) {
    throw runtime_error(format("expected 2 lines, got {}", lines.size()));
  }

  const auto [_, times_str] =
      utils::split_once(lines.at(0), regex(":[[:blank:]]+"));
  const auto [__, dists_str] =
      utils::split_once(lines.at(1), regex(":[[:blank:]]+"));

  const vector<time_t> times = read_vals(times_str);
  const vector<dist_t> dists = read_vals(dists_str);

  if (times.size() != dists.size()) {
    throw runtime_error(format("arity mismatch: {} times and {} dists",
                               times.size(), dists.size()));
  }

  races_t races;
  races.reserve(times.size());
  for (races_t::size_type i = 0; i < times.size(); ++i) {
    races.emplace_back(times.at(i), dists.at(i));
  }
  return races;
}

vector<result_t> get_winning_times(const race_t& race) {
  const time_t& t = race.first;
  const dist_t& d = race.second;

  vector<result_t> rs;
  for (result_t i = 1; i < t; ++i) {
    const auto v = i;
    const dist_t nd = (t - i) * v;
    if (nd > d) rs.push_back(i);
  }
  return rs;
}

result_t part_1(const lines_t& lines) {
  const races_t races = parse_lines(lines);
  auto times = races | views::transform(get_winning_times) |
               views::transform(
                   [](const vector<result_t>& times) { return times.size(); });
  const result_t r =
      accumulate(times.begin(), times.end(), 1, multiplies<result_t>());

  return r;
}

}  // namespace day_6
