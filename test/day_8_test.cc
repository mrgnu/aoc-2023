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
