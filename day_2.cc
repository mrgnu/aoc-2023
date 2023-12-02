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
}  // namespace

namespace day_2 {

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

  draws_t draws;

  const parts_t game_draw_strs =
      utils::split_string(game_draws[1], regex(";[[:blank:]]+"));

  for (const auto& game_draw : game_draw_strs) {
    const parts_t colors =
        utils::split_string(game_draw, regex(",[[:blank:]]+"));

    draw_t draw;
    for (const auto& color : colors) {
      smatch res;
      if (!regex_match(color, res, draw_re)) {
        throw runtime_error(format("failed to parse draw '{}'", game_draw));
      }
      const draw_t::count_t n = stoi(res[1]);
      const string color_str = res[2];
      const draw_t::color_t c = draw_t::s_color_map_.at(color_str);

      draw.count_map_[c] = n;
    }

    draws.push_back({
        draw,
    });
  }

  return {
      game_id,
      draws,
  };
}

// static
const map<string, draw_t::color_t> draw_t::s_color_map_{
    {
        "red",
        RED,
    },
    {
        "green",
        GREEN,
    },
    {
        "blue",
        BLUE,
    },
};

// TODO: move to utils
template <typename K, typename T>
constexpr inline T get_or(const map<K, T>& m, const K& k, const T fallback) {
  const auto it = m.find(k);
  return it == m.cend() ? fallback : it->second;
}

bool possible(const draw_t::count_map_t& bag_state, const game_t& game) {
  for (const auto& draw : game.draws_) {
    for (const auto& p : bag_state) {
      const auto& color = p.first;
      const auto& bag_count = p.second;
      const auto& draw_count =
          get_or<draw_t::color_t, draw_t::count_t>(draw.count_map_, color, 0);
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
          get_or<draw_t::color_t, draw_t::count_t>(min_cube_count, c, 0);
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
