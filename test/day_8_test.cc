#include "../day_8.hh"

#include <catch2/catch_test_macros.hpp>

#include "../utils.hh"

using namespace day_8;

const utils::lines_t example_1{
    "RL",
    "",
    "AAA = (BBB, CCC)",
    "BBB = (DDD, EEE)",
    "CCC = (ZZZ, GGG)",
    "DDD = (DDD, DDD)",
    "EEE = (EEE, EEE)",
    "GGG = (GGG, GGG)",
    "ZZZ = (ZZZ, ZZZ)",
};

const utils::lines_t example_2{
    // clang-format off
    "LLR",
    "",
    "AAA = (BBB, BBB)",
    "BBB = (AAA, ZZZ)",
    "ZZZ = (ZZZ, ZZZ)",
    // clang-format on
};

const utils::lines_t example_3{
    "LR",
    "",
    "11A = (11B, XXX)",
    "11B = (XXX, 11Z)",
    "11Z = (11B, XXX)",
    "22A = (22B, XXX)",
    "22B = (22C, 22C)",
    "22C = (22Z, 22Z)",
    "22Z = (22B, 22B)",
    "XXX = (XXX, XXX)",
};

TEST_CASE("parse_lines", "[day 8]") {
  REQUIRE(parse_lines(example_1) == input_t{
                                        "RL",
                                        map_t{
                                            {"AAA", {"BBB", "CCC"}},
                                            {"BBB", {"DDD", "EEE"}},
                                            {"CCC", {"ZZZ", "GGG"}},
                                            {"DDD", {"DDD", "DDD"}},
                                            {"EEE", {"EEE", "EEE"}},
                                            {"GGG", {"GGG", "GGG"}},
                                            {"ZZZ", {"ZZZ", "ZZZ"}},
                                        },
                                    });
}

TEST_CASE("part 1 example 1", "[day 8]") { REQUIRE(part_1(example_1) == 2); }
TEST_CASE("part 1 example 2", "[day 8]") { REQUIRE(part_1(example_2) == 6); }

TEST_CASE("part 1", "[day 8]") {
  REQUIRE(part_1(utils::read_lines("res/day_8_part_1.txt")) == 13939);
}

TEST_CASE("part 2 example 3", "[day 8]") { REQUIRE(part_2(example_3) == 6); }

TEST_CASE("part 2", "[day 8]") {
  REQUIRE(part_2(utils::read_lines("res/day_8_part_1.txt")) <
          18446744072555785741UL);
  REQUIRE(part_2(utils::read_lines("res/day_8_part_1.txt")) == 8906539031197UL);
}
