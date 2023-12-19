#include "../day_10.hh"

#include <catch2/catch_test_macros.hpp>

#include "../utils.hh"

namespace std {
template <typename A, typename B>
ostream& operator<<(ostream& os, const std::pair<A, B>& p) {
  os << "[" << p.first << ", " << p.second << "]";
  return os;
}
}  // namespace std

using namespace day_10;

const utils::lines_t square_clean{
    // clang-format off
  ".....",
  ".S-7.",
  ".|.|.",
  ".L-J.",
  ".....",
    // clang-format on
};

const utils::lines_t square{
    // clang-format off
    "-L|F7",
    "7S-7|",
    "L|7||",
    "-L-J|",
    "L|-JF",
    // clang-format on
};

const utils::lines_t complex{
    // clang-format off
    "7-F7-",
    ".FJ|7",
    "SJLL7",
    "|F--J",
    "LJ.LJ",
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

TEST_CASE("find_start_tile", "[day 10]") {
  const utils::lines_t clean{
      // clang-format off
    ".....",
    ".S-7.",
    ".|.|.",
    ".L-J.",
    ".....",
      // clang-format on
  };

  REQUIRE(find_start_tile(parse_map(square_clean)) ==
          std::pair<coord_t, tile_t>{{1, 1}, 'F'});
  REQUIRE(find_start_tile(parse_map(square)) ==
          std::pair<coord_t, tile_t>{{1, 1}, 'F'});
  REQUIRE(find_start_tile(parse_map(complex)) ==
          std::pair<coord_t, tile_t>{{0, 2}, 'F'});
}

TEST_CASE("example 1", "[day 10]") {
  REQUIRE(part_1(square_clean) == 4);
  REQUIRE(part_1(square) == 4);
  REQUIRE(part_1(complex) == 8);
}

TEST_CASE("part 1", "[day 10]") {
  REQUIRE(part_1(utils::read_lines("res/day_10_part_1.txt")) == 7102);
}

TEST_CASE("part 2", "[day 10]") {
  REQUIRE(part_2(utils::read_lines("res/day_10_part_1.txt")) == 363);
}
