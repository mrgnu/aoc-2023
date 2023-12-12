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
