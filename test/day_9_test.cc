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
