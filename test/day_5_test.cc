#include "../day_5.hh"

#include <catch2/catch_test_macros.hpp>

#include "../utils.hh"

namespace std {

template <typename T>
ostream& operator<<(ostream& os, const vector<T>& v) {
  os << v.size() << " element vector" << endl;
  for (const auto& e : v) {
    os << "- " << e << endl;
  }
  return os;
}

ostream& operator<<(ostream& os, const day_5::range_map_t& r) {
  os << "range map:" << endl;
  os << "- dest start:  " << get<0>(r) << endl;
  os << "- src start:   " << get<1>(r) << endl;
  os << "- range count: " << get<2>(r) << endl;
  return os;
}

template <typename A, typename B>
ostream& operator<<(ostream& os, const pair<A, B>& p) {
  os << "[" << p.first << "; " << p.second << "]";
  return os;
}

}  // namespace std

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

TEST_CASE("parse_input", "[day 5]") {
  // NOTE: range maps are sorted on source start
  const input_t expected_partial{
      // seeds
      {79, 14, 55, 13},
      categories_t{
          category_t{
              "seed-to-soil map",
              range_maps_t{
                  {52, 50, 48},
                  {50, 98, 2},
              },
          },
          category_t{
              "soil-to-fertilizer map",
              range_maps_t{
                  {39, 0, 15},
                  {0, 15, 37},
                  {37, 52, 2},
              },
          },
      },
  };

  const input_t actual = parse_input(example_lines);
  REQUIRE(actual.first == expected_partial.first);
  REQUIRE(actual.second.size() == 7);
  REQUIRE(actual.second.at(0) == expected_partial.second.at(0));
  REQUIRE(actual.second.at(1) == expected_partial.second.at(1));
}

TEST_CASE("example 1", "[day 5]") { REQUIRE(part_1(example_lines) == 35); }

TEST_CASE("part 1", "[day 5]") {
  REQUIRE(part_1(read_lines("res/day_5_part_1.txt")) == 806029445);
}
