#include "../utils.hh"

#include <catch2/catch_test_macros.hpp>

using namespace utils;

TEST_CASE("read_lines", "[utils][read_lines]") {
  lines_t expected{
      "foo",
      "i'm like a prickly pear!",
      "bar",
  };
  REQUIRE(read_lines("res/utils_lines.txt") == expected);
}

TEST_CASE("split_string", "[utils][split_string]") {
  std::regex p("; ");

  REQUIRE(split_string("", p) == parts_t{
                                     "",
                                 });
  REQUIRE(split_string("; ", p) == parts_t{
                                       "",
                                   });

  REQUIRE(split_string("foo", p) == parts_t{
                                        "foo",
                                    });
  REQUIRE(split_string("foo; ", p) == parts_t{
                                          "foo",
                                      });
  REQUIRE(split_string("; foo", p) == parts_t{
                                          "",
                                          "foo",
                                      });

  REQUIRE(split_string(" foo ; bar;  baz ", p) == parts_t{
                                                      " foo ",
                                                      "bar",
                                                      " baz ",
                                                  });
}
