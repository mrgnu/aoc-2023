#include "../day_12.hh"

#include <catch2/catch_test_macros.hpp>

#include "../utils.hh"

using namespace day_12;

TEST_CASE("is_valid", "[day 12]") {
  const utils::lines_t lines{
      // clang-format off
    ".###.##.#...",
    ".###.##..#..",
    ".###.##...#.",
    ".###.##....#",
    ".###..##.#..",
    ".###..##..#.",
    ".###..##...#",
    ".###...##.#.",
    ".###...##..#",
    ".###....##.#",
      // clang-format on
  };

  for (const utils::line_t& line : lines) {
    REQUIRE(is_valid(line, {3, 2, 1}));
  }

  for (const utils::line_t& line : lines) {
    REQUIRE(!is_valid(line, {2, 2, 1}));
  }

  for (const utils::line_t& line : lines) {
    REQUIRE(!is_valid(line, {2, 3, 1}));
  }

  for (const utils::line_t& line : lines) {
    REQUIRE(!is_valid(line, {2, 3, 2}));
  }
}

TEST_CASE("count_arrs", "[day 12]") {
  REQUIRE(part_1({"???.### 1,1,3"}) == 1);
  REQUIRE(part_1({".??..??...?##. 1,1,3"}) == 4);
  REQUIRE(part_1({"?#?#?#?#?#?#?#? 1,3,1,6"}) == 1);
  REQUIRE(part_1({"????.#...#... 4,1,1"}) == 1);
  REQUIRE(part_1({"????.######..#####. 1,6,5"}) == 4);
  REQUIRE(part_1({"?###???????? 3,2,1"}) == 10);
}

TEST_CASE("example 1", "[day 12]") {
  const utils::lines_t lines{
      // clang-format off
    "???.### 1,1,3",
    ".??..??...?##. 1,1,3",
    "?#?#?#?#?#?#?#? 1,3,1,6",
    "????.#...#... 4,1,1",
    "????.######..#####. 1,6,5",
    "?###???????? 3,2,1",
      // clang-format on
  };

  REQUIRE(part_1(lines) == 21);
}

TEST_CASE("part 1", "[day 12]") {
  REQUIRE(part_1(utils::read_lines("res/day_12_part_1.txt")) == 7916);
}
