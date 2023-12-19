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
