#include "../day_5.hh"

#include <catch2/catch_test_macros.hpp>

#include "../utils.hh"

using namespace utils;
using namespace day_5;

TEST_CASE("get_dest", "[day 5]") {
  // NOTE: sorted on source start
  const range_maps_t range_maps{
      {52, 50, 48},
      {50, 98, 2},
  };

  REQUIRE(get_dest(range_maps, 98) == 50);
  REQUIRE(get_dest(range_maps, 99) == 51);
  REQUIRE(get_dest(range_maps, 100) == 100);

  REQUIRE(get_dest(range_maps, 49) == 49);
  REQUIRE(get_dest(range_maps, 50) == 52);
  REQUIRE(get_dest(range_maps, 53) == 55);
  REQUIRE(get_dest(range_maps, 97) == 99);
}
