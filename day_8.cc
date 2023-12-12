#include "day_8.hh"

#include <format>

using namespace std;
using namespace utils;

namespace {

using namespace day_8;

map_t::value_type parse_mapping(const line_t& line) {
  static const string coord_pat = "[[:alpha:]]{3}";
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

}  // namespace day_8
