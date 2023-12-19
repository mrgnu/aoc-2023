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
