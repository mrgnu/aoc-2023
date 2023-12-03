#include "../day_2.hh"

#include <catch2/catch_test_macros.hpp>

#include "../utils.hh"

using namespace utils;
using namespace day_2;

namespace day_2 {

bool operator==(const draw_t& a, const draw_t& b) {
  return a.count_map_ == b.count_map_;
}

bool operator==(const game_t& a, const game_t& b) {
  return a.game_id_ == b.game_id_ && a.draws_ == b.draws_;
}

}  // namespace day_2

TEST_CASE("game::parse", "[day 2][game]") {
  const line_t game_str =
      "Game 1: 3 blue, 4 red; 1 red, 2 green, 6 blue; 2 green";

  const game_t::game_id_t game_id = 1;
  const game_t::draws_t draws{
      draw_t{draw_t::count_map_t{{draw_t::BLUE, 3}, {draw_t::RED, 4}}},
      draw_t{draw_t::count_map_t{
          {draw_t::RED, 1}, {draw_t::GREEN, 2}, {draw_t::BLUE, 6}}},
      draw_t{draw_t::count_map_t{{draw_t::GREEN, 2}}},
  };

  const game_t expected{
      game_id,
      draws,
  };

  REQUIRE(expected == game_t::parse(game_str));
}

TEST_CASE("part 1", "[day 2][part 1]") {
  REQUIRE(part_1(example_lines) == 8L);
  REQUIRE(part_1(read_lines("res/day_2_part_1.txt")) == 2076L);
}

TEST_CASE("part 2", "[day 2][part 2]") {
  REQUIRE(part_2(example_lines) == 2286L);
  REQUIRE(part_2(read_lines("res/day_2_part_1.txt")) == 70950L);
}
