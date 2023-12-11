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

result_t exp_f(const result_t v) {
  return pow(10, static_cast<result_t>(ceil(log10(v))));
}

race_t apply_kerning(const races_t& races) {
  time_t t = 0;
  dist_t d = 0;
  for (const race_t& race : races) {
    const auto& [rt, rd] = race;

    t = t * exp_f(rt) + rt;
    d = d * exp_f(rd) + rd;
  }
  return {t, d};
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

  // v = t
  // d = (T - t) * v
  // d = T*t - t*t
  // t*t - T*t + d = 0
  const result_t b = -t;
  const result_t c = d + 1;  // NOTE: +1 to make sure it's a win and not a tie
  const double sq = sqrt(b * b - 4 * c);
  array<double, 2> xs{
      (-b + sq) / 2.0,
      (-b - sq) / 2.0,
  };
  sort(xs.begin(), xs.end());

  const result_t l = ceil(xs.at(0));
  const result_t r = floor(xs.at(1));

  vector<result_t> rs;
  rs.reserve(r - l + 1);
  for (result_t i = l; i <= r; ++i) {
    rs.push_back(i);
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

result_t part_2(const lines_t& lines) {
  const races_t races = parse_lines(lines);
  const race_t kerned = apply_kerning(races);
  const result_t r = get_winning_times(kerned).size();
  return r;
}

}  // namespace day_6
