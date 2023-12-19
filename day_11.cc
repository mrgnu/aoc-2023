#include "day_11.hh"

#include <cmath>
#include <set>

using namespace utils;

namespace {

using namespace day_11;

using dimens_t = std::set<dimen_t>;

// galaxies, used x dimens
using parse_line_t = std::pair<galaxies_t, dimens_t>;

parse_line_t parse_line(const line_t& line, const dimen_t y) {
  dimens_t xs;
  galaxies_t galaxies;
  for (dimen_t x = 0; x < line.size(); ++x) {
    const auto& c = line[x];
    if (c != '#') continue;
    galaxies.insert({x, y});
    xs.insert(x);
  }
  return {galaxies, xs};
}

galaxies_t parse_input(const lines_t& lines, const dimen_t exp_rate) {
  dimens_t xs;
  galaxies_t map;

  dimen_t y = 0;
  for (const line_t& line : lines) {
    const auto [galaxies, row_xs] = parse_line(line, y);
    if (row_xs.empty()) {
      // no galaxies in row - expand by increasing y
      y += exp_rate;
    } else {
      map.insert(galaxies.cbegin(), galaxies.cend());
      xs.insert(row_xs.cbegin(), row_xs.cend());
    }
    ++y;
  }

  if (xs.empty()) return map;

  // empty rows are expanded, now for cols

  const dimen_t max_x = *xs.rbegin();
  // mappings from unexpanded to expanded x
  std::map<dimen_t, dimen_t> x_exp_map;
  dimen_t exp_x = 0;
  for (dimen_t x = 0; x <= max_x; ++x, ++exp_x) {
    if (xs.contains(x)) {
      x_exp_map[x] = exp_x;
    } else {
      // no galaxies in col - expand
      exp_x += exp_rate;
    }
  }

  galaxies_t expanded;
  for (const auto& ic : map) {
    const coord_t oc = {x_exp_map[ic.first], ic.second};
    expanded.insert(oc);
  }
  return expanded;
}

dimen_t distance(const coord_t& from, const coord_t& to) {
  return std::abs(to.first - from.first) + std::abs(to.second - from.second);
}

dimen_t acc_distances(const galaxies_t& map) {
  dimen_t acc = 0;
  for (auto g_it = map.cbegin(); g_it != map.cend(); ++g_it) {
    for (auto p_it = std::next(g_it); p_it != map.cend(); ++p_it) {
      acc += distance(*g_it, *p_it);
    }
  }
  return acc;
}

}  // namespace

namespace day_11 {

galaxies_t parse_map(const utils::lines_t& lines, const dimen_t exp_rate) {
  return parse_input(lines, exp_rate);
}

dimen_t part_1(const utils::lines_t& lines) {
  const galaxies_t map = parse_map(lines, 1);
  return acc_distances(map);
}

dimen_t part_2(const utils::lines_t& lines, dimen_t exp_rate) {
  const galaxies_t map = parse_map(lines, exp_rate);
  return acc_distances(map);
}

}  // namespace day_11
