#include "../utils.hh"

#include <catch2/catch_test_macros.hpp>

using namespace utils;

TEST_CASE("read_lines", "[utils]") {
  lines_t expected{
      "foo",
      "i'm like a prickly pear!",
      "bar",
  };
  REQUIRE(read_lines("res/utils_lines.txt") == expected);
}
