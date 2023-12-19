#include "day_10.hh"

#include <format>
#include <limits>
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

tile_t tile_at(const map_t& map, const coord_t& c) {
  auto it = map.find(c);
  return it == map.cend() ? '.' : it->second;
}

// get inverse / "from" direction for dir.
// e.g., if tile connects TO left, this returns FROM right.
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
    default:
      throw std::logic_error("unsupported dir");
  };
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
    default:
      throw std::logic_error("unsupported dir");
  }
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
      const tile_t& nt = tile_at(map, nc);
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

// called for each node in path, starting with start node. return
// false to stop. otherwise, stops before reaching start again.
using visitor_t = std::function<bool(const coord_t& c)>;

void walk_path(const input_t& input, visitor_t visit, bool reverse = false) {
  const auto& [start_coord, map] = input;
  const tile_t start_type = map.at(start_coord);
  dir_t dir = reverse ? *(std::next(s_tile_connections.at(start_type).begin()))
                      : *(s_tile_connections.at(start_type).begin());
  coord_t c = start_coord;

  do {
    if (!visit(c)) break;
    c = move(c, dir);
    const tile_t t = map.at(c);
    auto it = s_tile_connections.at(t).begin();
    if (*it == other_dir(dir)) ++it;
    dir = *it;
  } while (c != start_coord);
}

using dist_map_t = std::map<coord_t, dist_t>;

dist_map_t create_distance_map(const input_t& input) {
  dist_map_t dist_map;
  dist_t dist;

  // walk loop one direction and set distances
  dist = 0;
  walk_path(input, [&dist_map, &dist](const coord_t& c) {
    dist_map[c] = dist++;
    return true;
  });

  // walk loop other direction and update distances as long as they're smaller
  dist = 0;
  walk_path(
      input,
      [&dist_map, &dist](const coord_t& c) {
        auto dist_it = dist_map.find(c);
        if (dist_it->second < dist) return false;
        dist_it->second = dist++;
        return true;
      },
      true);

  return dist_map;
}

using coords_t = std::set<coord_t>;

coords_t find_enclosed_coords(const input_t& input) {
  // collect loop coords
  coords_t loop_coords;
  walk_path(input, [&loop_coords](const coord_t& c) {
    loop_coords.insert(c);
    return true;
  });

  // figure out limits of loop
  std::pair<dimen_t, dimen_t> x_lims{std::numeric_limits<dimen_t>::max(), 0};
  std::pair<dimen_t, dimen_t> y_lims = x_lims;
  for (const coord_t& c : loop_coords) {
    x_lims.first = std::min(x_lims.first, c.first);
    x_lims.second = std::max(x_lims.second, c.first);
    y_lims.first = std::min(y_lims.first, c.second);
    y_lims.second = std::max(y_lims.second, c.second);
  }

  const map_t& map = input.second;

  // collect enclosed coords
  coords_t enclosed_coords;
  for (dimen_t y = y_lims.first; y <= y_lims.second; ++y) {
    size_t cross_count = 0;
    for (dimen_t x = x_lims.first; x <= x_lims.second; ++x) {
      const coord_t c{x, y};

      // if tile isn't part of loop, it's enclosed if cross_count is odd
      if (loop_coords.find(c) == loop_coords.end()) {
        if (cross_count % 2) enclosed_coords.insert(c);
        continue;
      }

      const auto& t = map.at(c);
      if (t == '|') {
        ++cross_count;
        continue;
      }

      const std::set<dir_t>& start_conns = s_tile_connections.at(t);
      assert(start_conns.contains(RIGHT));
      while (++x < x_lims.second && map.at({x, y}) == '-') {
        // skip horizontal streak
      }
      const std::set<dir_t>& end_conns = s_tile_connections.at(map.at({x, y}));
      assert(end_conns.contains(LEFT));

      // NOTE: verticals come first
      // if they're equal line isn't crossing - e.g. L--J or F-7
      if (*start_conns.cbegin() == *end_conns.cbegin()) continue;
      ++cross_count;
    }
  }

  return enclosed_coords;
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

input_t parse_input(const lines_t& lines) {
  map_t map = parse_map(lines);
  auto [start_coord, start_tile] = find_start_tile(map);
  map[start_coord] = start_tile;
  return {start_coord, map};
}

std::pair<coord_t, tile_t> find_start_tile(const map_t& map) {
  return ::find_start_tile(map);
}

dist_t part_1(const lines_t& lines) {
  const input_t input = parse_input(lines);
  const dist_map_t dist_map = create_distance_map(input);
  auto dists =
      dist_map | std::views::transform([](const auto& p) { return p.second; });
  dist_t m = 0;
  for (const auto& d : dists) {
    m = std::max(m, d);
  }
  return m;
}

size_t part_2(const lines_t& lines) {
  const input_t input = parse_input(lines);
  const coords_t enclosed = find_enclosed_coords(input);
  return enclosed.size();
}

}  // namespace day_10
