#include "../day_11.hh"

#include <catch2/catch_test_macros.hpp>

#include "../utils.hh"

namespace std {
template <typename A, typename B>
ostream& operator<<(ostream& os, const std::pair<A, B>& p) {
  os << "[" << p.first << ", " << p.second << "]";
  return os;
}
}  // namespace std

const utils::lines_t example_1{
    // clang-format off
  "...#......",
  ".......#..",
  "#.........",
  "..........",
  "......#...",
  ".#........",
  ".........#",
  "..........",
  ".......#..",
  "#...#.....",
    // clang-format on
};

using namespace day_11;

TEST_CASE("parse_map", "[day 11]") {
  REQUIRE(parse_map(example_1) == galaxies_t{
                                      coord_t{4, 0},
                                      coord_t{9, 1},
                                      coord_t{0, 2},
                                      coord_t{8, 5},
                                      coord_t{1, 6},
                                      coord_t{12, 7},
                                      coord_t{9, 10},
                                      coord_t{0, 11},
                                      coord_t{5, 11},
                                  });
}

TEST_CASE("example 1", "[day 11]") { REQUIRE(part_1(example_1) == 374); }

TEST_CASE("part 1", "[day 11]") {
  REQUIRE(part_1(utils::read_lines("res/day_11_part_1.txt")) == 9742154);
}

TEST_CASE("example 2", "[day 11]") {
  REQUIRE(part_2(example_1, 10 - 1) == 1030);
  REQUIRE(part_2(example_1, 100 - 1) == 8410);
}

TEST_CASE("part 2", "[day 11]") {
  REQUIRE(part_2(utils::read_lines("res/day_11_part_1.txt")) == 411142919886L);
}
