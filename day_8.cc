#include "day_8.hh"

#include <format>

using namespace std;
using namespace utils;

namespace {

using namespace day_8;

map_t::value_type parse_mapping(const line_t& line) {
  static const string coord_pat = "[[:alnum:]]{3}";
  regex pat(
      format("^({}) = \\(({}), ({})\\)$", coord_pat, coord_pat, coord_pat));
  smatch m;
  if (!regex_match(line, m, pat)) {
    throw runtime_error(format("'{}' doesn't conform to mapping", line));
  }

  const coord_t from = m[1];
  const coord_t left = m[2];
  const coord_t right = m[3];

  return {from, {left, right}};
}

vector<coord_t> walk(const input_t& input, const coord_t& from,
                     const coord_t& to) {
  const directions_t& dirs = input.first;
  const map_t& map = input.second;

  directions_t::size_type i = 0;
  coord_t c = from;
  vector<coord_t> path;
  while (c != to) {
    const coords_t& cs = map.at(c);
    const direction_t& d = dirs[i];
    ++i;
    while (i >= dirs.size()) i -= dirs.size();
    c = (d == 'L') ? cs.first : cs.second;
    path.push_back(c);
  }

  return path;
}

vector<coord_t> walk(const input_t& input) { return walk(input, "AAA", "ZZZ"); }

}  // namespace

namespace day_8 {

input_t parse_lines(const lines_t& lines) {
  auto it = lines.cbegin();
  const directions_t directions = *it++;
  if (*it++ != "") {
    throw runtime_error("expected blank line after directions");
  }

  map_t map;
  for (; it != lines.cend(); ++it) {
    map.insert(parse_mapping(*it));
  }

  return {directions, map};
}

result_t part_1(const lines_t& lines) {
  const input_t input = parse_lines(lines);
  const vector<coord_t> path = walk(input);
  return path.size();
}

}  // namespace day_8
