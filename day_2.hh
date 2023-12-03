#pragma once

#include <map>
#include <string>
#include <vector>

#include "utils.hh"

namespace day_2 {

const utils::lines_t example_lines{
    "Game 1: 3 blue, 4 red; 1 red, 2 green, 6 blue; 2 green",
    "Game 2: 1 blue, 2 green; 3 green, 4 blue, 1 red; 1 green, 1 blue",
    "Game 3: 8 green, 6 blue, 20 red; 5 blue, 4 red, 13 green; 5 green, 1 "
    "red",
    "Game 4: 1 green, 3 red, 6 blue; 3 green, 6 red; 3 green, 15 blue, 14 "
    "red",
    "Game 5: 6 red, 1 blue, 3 green; 2 blue, 1 red, 2 green",
};

using result_t = unsigned long;

struct draw_t {
  enum color_t {
    RED,
    GREEN,
    BLUE,
  };

  using color_map_t = std::map<std::string, color_t>;
  using count_t = result_t;
  using count_map_t = std::map<color_t, count_t>;

  static const color_map_t s_color_map_;

  count_map_t count_map_;
};

struct game_t {
  using game_id_t = size_t;
  using draws_t = std::vector<draw_t>;

  static game_t parse(const utils::line_t& line);

  const game_id_t game_id_;
  const draws_t draws_;
};

result_t part_1(const utils::lines_t& lines);

result_t part_2(const utils::lines_t& lines);

}  // namespace day_2
