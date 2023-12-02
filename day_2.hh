#pragma once

#include <map>
#include <string>
#include <vector>

#include "utils.hh"

namespace day_2 {

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
