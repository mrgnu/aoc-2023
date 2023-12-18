#include "day_10.hh"

#include <format>
#include <ranges>
#include <set>

using namespace utils;

namespace {

using namespace day_10;

static const std::map<tile_t, std::set<dir_t>> s_tile_connections{
    // clang-format off
    {'|', {UP, DOWN}},
    {'-', {LEFT, RIGHT}},
    {'L', {RIGHT, UP}},
    {'J', {LEFT, UP}},
    {'7', {LEFT, DOWN}},
    {'F', {RIGHT, DOWN}},
    // clang-format on
};

static const std::set<dir_t> s_dirs{LEFT, UP, RIGHT, DOWN};

tile_t get_tile(const map_t& map, const coord_t& c) {
  auto it = map.find(c);
  return it == map.cend() ? '.' : it->second;
}

constexpr dir_t other_dir(const dir_t& dir) {
  switch (dir) {
    case LEFT:
      return RIGHT;
    case UP:
      return DOWN;
    case RIGHT:
      return LEFT;
    case DOWN:
      return UP;
  };

  throw std::runtime_error("failed to get other dir");
}

constexpr coord_t move(const coord_t& c, const dir_t d) {
  switch (d) {
    case LEFT:
      return {c.first - 1, c.second};
    case RIGHT:
      return {c.first + 1, c.second};
    case UP:
      return {c.first, c.second - 1};
    case DOWN:
      return {c.first, c.second + 1};
  }

  throw std::runtime_error("failed to move");
}

std::vector<map_t::value_type> parse_line(const line_t& line, const dimen_t y) {
  std::vector<map_t::value_type> tiles;
  for (dimen_t x = 0; x < line.size(); ++x) {
    tiles.push_back({{x, y}, line[x]});
  }
  return tiles;
}

std::pair<coord_t, tile_t> find_start_tile(const map_t& map) {
  auto start_pair_range =
      map | std::views::filter(
                [](const map_t::value_type& p) { return p.second == 'S'; });
  const coord_t& sc = start_pair_range.front().first;

  for (const auto& p : s_tile_connections) {
    const tile_t& t = p.first;
    const auto& dirs = p.second;

    int match_count = 0;
    for (const dir_t& dir : dirs) {
      const coord_t nc = move(sc, dir);
      const tile_t& nt = get_tile(map, nc);
      if (nt == '.') continue;
      for (const dir_t& nd : s_tile_connections.at(nt)) {
        if (dir == other_dir(nd)) ++match_count;
      }
    }
    if (match_count == dirs.size()) {
      return {sc, t};
    }
  }
  throw std::runtime_error(
      std::format("no tile type connects {}:{}", sc.first, sc.second));
}

}  // namespace

namespace day_10 {

map_t parse_map(const lines_t& lines) {
  map_t map;
  for (dimen_t y = 0; y < lines.size(); ++y) {
    const line_t& line = lines.at(y);
    auto tiles = parse_line(line, y);
    map.insert(tiles.begin(), tiles.end());
  }
  return map;
}

std::pair<coord_t, tile_t> find_start_tile(const map_t& map) {
  return ::find_start_tile(map);
}

}  // namespace day_10
