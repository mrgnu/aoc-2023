#include "day_2.hh"

#include <algorithm>
#include <format>
#include <functional>
#include <numeric>
#include <ranges>
#include <regex>
#include <utility>

using namespace std;
using namespace utils;

namespace {
const regex draw_re("([[:digit:]]+)[[:blank:]]+([[:alpha:]]+)",
                    regex::extended);

using namespace day_2;

pair<draw_t::color_t, draw_t::count_t> parse_color(const part_t& color_str) {
  smatch res;
  if (!regex_match(color_str, res, draw_re)) {
    throw runtime_error(format("failed to parse color '{}'", color_str));
  }
  const draw_t::count_t n = stoi(res[1]);
  const draw_t::color_t c = draw_t::s_color_map_.at(res[2]);
  return {c, n};
}

draw_t parse_draw(const string& draw_str) {
  const parts_t colors = utils::split_string(draw_str, regex(",[[:blank:]]+"));
  auto pairs = colors | views::transform(parse_color) | views::common;
  draw_t draw;
  draw.count_map_.insert(pairs.begin(), pairs.end());
  return draw;
}

game_t::draws_t parse_draws(const string& draws_str) {
  const parts_t draw_strs =
      utils::split_string(draws_str, regex(";[[:blank:]]+"));
  auto view = draw_strs | views::transform(parse_draw) | views::common;
  game_t::draws_t draws;
  copy(view.begin(), view.end(), back_inserter(draws));
  return draws;
}

}  // namespace

namespace day_2 {

// static
const map<string, draw_t::color_t> draw_t::s_color_map_{
    {"red", RED},
    {"green", GREEN},
    {"blue", BLUE},
};

// static
game_t game_t::parse(const line_t& line) {
  const parts_t game_draws = utils::split_string(line, regex(":[[:blank:]]+"));
  if (game_draws.size() != 2) {
    throw runtime_error(format("couldn't split '{}'", line));
  }

  const string& game_str = game_draws[0];
  smatch g;
  if (!regex_match(game_str, g, regex("Game ([[:digit:]]+)"))) {
    throw runtime_error(format("failed to parse game '{}'", game_str));
  }

  const game_id_t game_id = stoi(g[1]);

  const string& draws_str = game_draws[1];
  const draws_t draws = ::parse_draws(draws_str);

  return {
      game_id,
      draws,
  };
}

#include "get_or.inl"

bool possible(const draw_t::count_map_t& bag_state, const game_t& game) {
  for (const auto& draw : game.draws_) {
    for (const auto& p : bag_state) {
      const auto& color = p.first;
      const auto& bag_count = p.second;
      const auto& draw_count = utils::get_or<draw_t::color_t, draw_t::count_t>(
          draw.count_map_, color, 0);
      if (bag_count < draw_count) return false;
    }
  }
  return true;
}

auto get_possible_games(const draw_t::count_map_t& bag_state,
                        const lines_t& lines) {
  auto possible_bind = bind(possible, bag_state, placeholders::_1);
  const auto games =
      lines | views::transform(game_t::parse) | views::filter(possible_bind);
  return games;
}

result_t part_1(const lines_t& lines) {
  const draw_t::count_map_t bag_state{
      {draw_t::RED, 12},
      {draw_t::GREEN, 13},
      {draw_t::BLUE, 14},
  };
  auto possible_bind = bind(possible, bag_state, placeholders::_1);
  auto game_id = [](const game_t& game) -> game_t::game_id_t {
    return game.game_id_;
  };

  auto games = get_possible_games(bag_state, lines);
  auto game_ids = games | views::transform(game_id) | views::common;
  return accumulate(game_ids.begin(), game_ids.end(), 0);
}

draw_t::count_map_t min_count_map(const game_t& game) {
  auto draw_it = game.draws_.cbegin();
  draw_t::count_map_t min_cube_count = draw_it->count_map_;
  ++draw_it;
  for (; draw_it != game.draws_.cend(); ++draw_it) {
    const auto& draw = *draw_it;
    for (const auto count_pair : draw.count_map_) {
      const auto& c = count_pair.first;
      const auto& n = count_pair.second;
      const draw_t::count_t old_min =
          utils::get_or<draw_t::color_t, draw_t::count_t>(min_cube_count, c, 0);
      min_cube_count[c] = max(old_min, n);
    }
  }
  return min_cube_count;
}

result_t cube_power(const draw_t::count_map_t& min_count) {
  auto counts = min_count |
                views::transform([](const auto& p) { return p.second; }) |
                views::common;
  return accumulate(counts.begin(), counts.end(), 1, multiplies<result_t>());
}

result_t part_2(const lines_t& lines) {
  auto powers = lines | views::transform(game_t::parse) |
                views::transform(min_count_map) | views::transform(cube_power) |
                views::common;
  const result_t sum = accumulate(powers.begin(), powers.end(), 0);
  return sum;
}

}  // namespace day_2
