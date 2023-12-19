#include "day_11.hh"

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

galaxies_t parse_input(const lines_t& lines) {
  dimens_t xs;
  galaxies_t map;

  dimen_t y = 0;
  for (const line_t& line : lines) {
    const auto [galaxies, row_xs] = parse_line(line, y);
    if (row_xs.empty()) {
      // no galaxies in this row - expand by increasing y - twice, because y
      // isn't increased by for loop
      y += 2;
      continue;
    }
    map.insert(galaxies.cbegin(), galaxies.cend());
    xs.insert(row_xs.cbegin(), row_xs.cend());
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
      ++exp_x;
    }
  }

  galaxies_t expanded;
  for (const auto& ic : map) {
    const coord_t oc = {x_exp_map[ic.first], ic.second};
    expanded.insert(oc);
  }
  return expanded;
}

}  // namespace

namespace day_11 {

galaxies_t parse_map(const utils::lines_t& lines) { return parse_input(lines); }

}  // namespace day_11
