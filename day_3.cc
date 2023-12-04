#include "day_3.hh"

#include <algorithm>
#include <functional>
#include <iostream>
#include <numeric>
#include <ranges>
#include <sstream>

namespace std {
template <typename A, typename B>
ostream& operator<<(ostream& o, const std::pair<A, B>& p) {
  o << "[" << p.first << "; " << p.second << "]";
  return o;
}
}  // namespace std

using namespace std;
using namespace utils;

namespace {

using namespace day_3;
using day_3::part_t;

result_t get_num(line_t::const_iterator& it, const line_t::const_iterator end) {
  const auto start = it;
  while (it != end && isdigit(*it)) ++it;
  const line_t num_str(start, it);
  return stoi(num_str);
}

vector<schematic_t::value_type> parse_row(const line_t& line, const dim_t y) {
  vector<schematic_t::value_type> tiles;

  for (auto it = line.cbegin(); it != line.cend();) {
    const coord_t c = {distance(line.cbegin(), it), y};

    if (*it == '.') {
      ++it;
      continue;
    }

    if (isdigit(*it)) {
      // NOTE: part numbers are added for each tile they cover.
      // part_num_t::second is the coord of the leftmost tile of the part
      // number.
      const result_t n = get_num(it, line.cend());
      const dim_t end_x = distance(line.cbegin(), it);
      for (dim_t x = c.first; x < end_x; ++x) {
        const part_num_t num{n, c};
        const coord_t t{x, y};
        const val_t v(num);
        tiles.push_back({t, v});
      }

      continue;
    }

    tiles.push_back({c, *it});
    ++it;
  }

  return tiles;
}

template <typename T>
auto coords_with_type(const schematic_t& schematic) {
  return schematic | views::filter([](const schematic_t::value_type& p) {
           return holds_alternative<T>(p.second);
         }) |
         views::transform([](const schematic_t::value_type& p) -> coord_t {
           return p.first;
         });
}

template <typename T>
auto coords_with_type(const schematic_t& schematic, auto& coords) {
  return coords | views::filter([&schematic](const coord_t& c) -> bool {
           const auto it = schematic.find(c);
           if (it == schematic.cend()) return false;
           return holds_alternative<T>(it->second);
         });
}

template <typename T>
T to_type(const schematic_t& schematic, const coord_t& coord) {
  try {
    return get<T>(schematic.at(coord));
  } catch (const exception& e) {
    cerr << "failed to get " << coord << " with specific type" << endl;
    throw e;
  }
}

template <typename T>
auto range_with_type(const schematic_t& schematic, auto& coord_range) {
  auto type_bind = bind(to_type<T>, ref(schematic), placeholders::_1);
  return coord_range | views::transform([&schematic](const coord_t& c) {
           return to_type<T>(schematic, c);
         });
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

coords_t adjacent_part_num_coords(const schematic_t& schematic,
                                  const coord_t& coord) {
  const coords_t adj = get_adjacent(coord);
  // keep coords of adjacent part numbers - this may contain more than
  // one coord for the same part number
  auto part_num_coords = coords_with_type<part_num_t>(schematic, adj);

  // collect start coords of part numbers
  auto part_num_range = range_with_type<part_num_t>(schematic, part_num_coords);
  coords_t coords;
  for (const part_num_t& part_num : part_num_range) {
    const coord_t& start = part_num.second;
    coords.insert(start);
  }

  return coords;
}

vector<result_t> gear_ratios(const schematic_t& schematic) {
  // range with coords for all '*' parts
  auto gear_type_coord_range =
      coords_with_type<part_t>(schematic) |
      views::filter([&schematic](const coord_t& coord) {
        const part_t part = to_type<part_t>(schematic, coord);
        return part == '*';
      });

  vector<result_t> ratios;
  for (const coord_t& coord : gear_type_coord_range) {
    const coords_t adjacent = adjacent_part_num_coords(schematic, coord);
    // must have exactly two adjacent numbers
    if (adjacent.size() != 2) continue;

    auto nums = range_with_type<part_num_t>(schematic, adjacent) |
                views::transform([](const part_num_t& part) -> result_t {
                  return part.first;
                });
    const result_t ratio =
        accumulate(nums.begin(), nums.end(), 1L, std::multiplies<result_t>());
    ratios.push_back(ratio);
  }
  return ratios;
}

}  // namespace

namespace day_3 {

schematic_t parse_schematic(const lines_t& lines) {
  schematic_t schematic;
  for (lines_t::size_type y = 0; y < lines.size(); ++y) {
    const line_t& line = lines[y];
    const vector<schematic_t::value_type> row = parse_row(line, y);
    schematic.insert(row.cbegin(), row.cend());
  }
  return schematic;
}

part_nums_t part_nums(const schematic_t& schematic) {
  auto part_coords = coords_with_type<part_t>(schematic);

  // collect start position of all adjacent part numbers
  set<coord_t> valid_part_num_coords;

  for (const coord_t& part_coord : part_coords) {
    const coords_t adjacent = adjacent_part_num_coords(schematic, part_coord);
    valid_part_num_coords.insert(adjacent.cbegin(), adjacent.cend());
  }

  // fetch and return.
  part_nums_t nums;
  for (const coord_t& coord : valid_part_num_coords) {
    nums.push_back(to_type<part_num_t>(schematic, coord));
  }
  return nums;
}

result_t part_1(const lines_t& lines) {
  const schematic_t s = parse_schematic(lines);
  const part_nums_t p = part_nums(s);
  auto nums = p | views::transform(
                      [](const part_num_t& p) -> result_t { return p.first; });
  const result_t r = accumulate(nums.begin(), nums.end(), 0);
  return r;
}

result_t part_2(const lines_t& lines) {
  const schematic_t s = parse_schematic(lines);
  const vector<result_t> ratios = gear_ratios(s);
  const result_t r = accumulate(ratios.cbegin(), ratios.cend(), 0);
  return r;
}

}  // namespace day_3
