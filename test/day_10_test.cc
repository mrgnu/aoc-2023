#include "../day_10.hh"

#include <catch2/catch_test_macros.hpp>

#include "../utils.hh"

const utils::lines_t example_input{};

using namespace day_10;

const utils::lines_t example_1_clean{
    // clang-format off
  ".....",
  ".F-7.",
  ".|.|.",
  ".L-J.",
  ".....",
    // clang-format on
};

TEST_CASE("parse_map", "[day 10]") {
  const utils::lines_t lines{
      "...",
      "F-7",
  };

  REQUIRE(parse_map(lines) == map_t{
                                  {{0, 0}, '.'},
                                  {{1, 0}, '.'},
                                  {{2, 0}, '.'},
                                  {{0, 1}, 'F'},
                                  {{1, 1}, '-'},
                                  {{2, 1}, '7'},
                              });
}
