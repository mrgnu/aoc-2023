#include "day_3.hh"

#include <algorithm>
#include <functional>
#include <numeric>
#include <ranges>
#include <sstream>

using namespace std;
using namespace utils;

namespace {

using namespace day_3;

using row_val_t = pair<dim_t, val_t>;
using row_t = vector<row_val_t>;

part_num_t get_num(line_t::const_iterator& it,
                   const line_t::const_iterator end) {
  const auto start = it;
  while (it != end && isdigit(*it)) ++it;
  const line_t num_str(start, it);
  return stoi(num_str);
}

row_t parse_row(const line_t& line) {
  row_t row;
  for (auto it = line.cbegin(); it != line.cend();) {
    const dim_t idx = distance(line.cbegin(), it);

    if (*it == '.') {
      ++it;
      continue;
    }

    if (isdigit(*it)) {
      const part_num_t n = get_num(it, line.cend());
      // NOTE: adding part number for leftmost x-coord it ocupies
      row.emplace_back(idx, n);
      continue;
    }

    row.emplace_back(idx, *it);
    ++it;
  }

  return row;
}

bool is_part(const schematic_t& schematic, const coord_t& coord) {
  const auto it = schematic.find(coord);
  if (it == schematic.cend()) return false;
  const val_t& v = it->second;

  // NOTE: get_if to avoid ambiguous type
  return get_if<1>(&v);
}

bool is_part_num(const schematic_t& schematic, const coord_t& coord) {
  const auto it = schematic.find(coord);
  if (it == schematic.cend()) return false;
  const val_t& v = it->second;

  // NOTE: get_if to avoid ambiguous type
  return get_if<0>(&v);
}

coords_t get_adjacent(const coord_t& coord) {
  const auto& x = coord.first;
  const auto& y = coord.second;
  return {
      // clang-format off
      { x - 1, y - 1 }, { x, y - 1 }, {x + 1, y - 1 },
      { x - 1, y     },               {x + 1, y     },
      { x - 1, y + 1 }, { x, y + 1 }, {x + 1, y + 1 },
      // clang-format on
  };
}

coords_t get_part_num_coords(const part_num_t& num,
                             const coord_t& start_coord) {
  const auto& y = start_coord.second;
  const line_t::size_type n = to_string(num).length();
  coords_t coords;
  for (auto x = start_coord.first; x < start_coord.first + n; ++x) {
    coords.emplace(x, y);
  }
  return coords;
}

bool is_assigned_part_num(const schematic_t& schematic, const coord_t& coord) {
  const auto it = schematic.find(coord);
  if (it == schematic.cend()) return false;
  const val_t& v = it->second;
  if (!holds_alternative<part_num_t>(v)) return false;

  const part_num_t& num = get<part_num_t>(v);
  const coords_t part_num_coords = get_part_num_coords(num, coord);
  for (const auto& part_num_coord : part_num_coords) {
    const coords_t adjacent = get_adjacent(part_num_coord);
    for (const coord_t& a : adjacent) {
      if (is_part(schematic, a)) return true;
    }
  }

  return false;
}

}  // namespace

namespace day_3 {

schematic_t parse_schematic(const lines_t& lines) {
  schematic_t schematic;
  for (lines_t::size_type y = 0; y < lines.size(); ++y) {
    const line_t& line = lines[y];
    const row_t row = parse_row(line);
    for (const auto& p : row) {
      const auto& x = p.first;
      const auto& v = p.second;
      const coord_t c{x, y};
      schematic[c] = v;
    }
  }
  return schematic;
}

part_nums_t part_nums(const schematic_t& schematic) {
  auto filter = [&schematic](const schematic_t::value_type& v) {
    return is_assigned_part_num(schematic, v.first);
  };
  auto get_part_num = [](const val_t& v) { return get<part_num_t>(v); };

  auto v = schematic | views::filter(filter) |
           views::transform(&schematic_t::value_type::second) |
           views::transform(get_part_num) | views::common;

  part_nums_t parts;
  std::copy(v.begin(), v.end(), inserter(parts, parts.begin()));
  return parts;
}

result_t part_1(const lines_t& lines) {
  const schematic_t s = parse_schematic(lines);
  const part_nums_t p = part_nums(s);
  const result_t r = accumulate(p.cbegin(), p.cend(), 0);
  return r;
}

}  // namespace day_3
