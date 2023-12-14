#include "../day_9.hh"

#include <catch2/catch_test_macros.hpp>

#include "../utils.hh"

const utils::lines_t example_input{
    "0 3 6 9 12 15",
    "1 3 6 10 15 21",
    "10 13 16 21 30 45",
};

using namespace day_9;

TEST_CASE("parse_input", "[day 9]") {
  REQUIRE(parse_input(example_input) == input_t{
                                            timeline_t{0, 3, 6, 9, 12, 15},
                                            timeline_t{1, 3, 6, 10, 15, 21},
                                            timeline_t{10, 13, 16, 21, 30, 45},
                                        });
}

TEST_CASE("predict", "[day 9]") {
  const input_t input = parse_input(example_input);
  REQUIRE(predict(input[0]) == 18);
  REQUIRE(predict(input[1]) == 28);
  REQUIRE(predict(input[2]) == 68);
}

TEST_CASE("example 1", "[day 9]") { REQUIRE(part_1(example_input) == 114); }

TEST_CASE("part 1", "[day 9]") {
  REQUIRE(part_1(utils::read_lines("res/day_9_part_1.txt")) == 1584748274);
}

TEST_CASE("example 2", "[day 9]") { REQUIRE(part_2(example_input) == 2); }

TEST_CASE("part 2", "[day 9]") {
  REQUIRE(part_2(utils::read_lines("res/day_9_part_1.txt")) == 1026);
}
