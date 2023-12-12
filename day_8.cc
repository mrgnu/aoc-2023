#include "day_8.hh"

#include <format>
#include <ranges>

#include "lcm.inl"

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

coord_t walk(const input_t& input, const coord_t& cur, const direction_t d) {
  const coords_t& cs = input.second.at(cur);
  return (d == 'L') ? cs.first : cs.second;
}

direction_t next_dir(const input_t& input, directions_t::size_type& i) {
  const directions_t& dirs = input.first;
  const direction_t& d = dirs[i];
  ++i;
  while (i >= dirs.size()) i -= dirs.size();
  return d;
}

vector<coord_t> walk(const input_t& input, const coord_t& from,
                     function<bool(const coord_t&)> done_p) {
  const directions_t& dirs = input.first;
  const map_t& map = input.second;

  directions_t::size_type i = 0;
  coord_t c = from;
  vector<coord_t> path;
  while (!done_p(c)) {
    const direction_t d = next_dir(input, i);
    c = walk(input, c, d);
    path.push_back(c);
  }

  return path;
}

vector<coord_t> walk(const input_t& input) {
  return walk(input, "AAA", [](const coord_t& c) { return c == "ZZZ"; });
}

result_t multi_walk(const input_t& input) {
  auto starts = input.second | views::keys |
                views::filter([](const coord_t& c) { return c.back() == 'A'; });
  vector<coord_t> cs;
  copy(starts.begin(), starts.end(), back_inserter(cs));

  auto done_p = [](const coord_t& c) -> bool { return c.back() == 'Z'; };

  vector<result_t> steps;
  steps.reserve(cs.size());

  for (const coord_t& c : cs) {
    const result_t s = walk(input, c, done_p).size();
    steps.push_back(s);
  }

  return lcm(steps);
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

result_t part_1(const lines_t& lines) {
  const input_t input = parse_lines(lines);
  const vector<coord_t> path = walk(input);
  return path.size();
}

result_t part_2(const lines_t& lines) {
  const input_t input = parse_lines(lines);
  return multi_walk(input);
}

}  // namespace day_8
