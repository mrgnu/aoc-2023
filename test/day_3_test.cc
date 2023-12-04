#include "../day_3.hh"

#include <catch2/catch_test_macros.hpp>

#include "../utils.hh"

namespace std {
template <typename A, typename B>
ostream& operator<<(ostream& o, const std::pair<A, B>& p) {
  o << "[" << p.first << "; " << p.second << "]";
  return o;
}
}  // namespace std

using namespace utils;
using namespace day_3;

TEST_CASE("parse_schematic lazy", "[day 3]") {
  const schematic_t s = parse_schematic(example_lines);

  const coord_t start{0, 0};
  REQUIRE(s.at({0, 0}) == val_t(part_num_t{467, start}));
  REQUIRE(s.at({1, 0}) == val_t(part_num_t{467, start}));
  REQUIRE(s.at({2, 0}) == val_t(part_num_t{467, start}));

  REQUIRE(s.at({3, 1}) == val_t('*'));
  REQUIRE(s.at({3, 8}) == val_t('$'));

  REQUIRE(s.find({3, 0}) == s.cend());
  REQUIRE(s.find({2, 1}) == s.cend());
}

TEST_CASE("part_nums", "[day 3]") {
  const schematic_t s = parse_schematic(example_lines);

  // NOTE: this test assumes no dups
  const part_nums_t actual_vec = part_nums(s);
  const std::set<part_num_t> actual_set(actual_vec.cbegin(), actual_vec.cend());

  const part_nums_t expected_vec{
      // clang-format off
    {467, {0, 0}},
    { 35, {2, 2}},
    {633, {6, 2}},
    {617, {0, 4}},
    {592, {2, 6}},
    {755, {6, 7}},
    {664, {1, 9}},
    {598, {5, 9}},
      // clang-format on
  };

  const std::set<part_num_t> expected_set(expected_vec.cbegin(),
                                          expected_vec.cend());
  REQUIRE(actual_set == expected_set);
}

TEST_CASE("example 1", "[day 3][part 1]") {
  REQUIRE(part_1(example_lines) == 4361);
}

TEST_CASE("part 1", "[day 3][part 1]") {
  const lines_t lines = read_lines("res/day_3_part_1.txt");
  REQUIRE(part_1(lines) > 326919);  // first guess
  REQUIRE(part_1(lines) == 521515);
}

TEST_CASE("example 2", "[day 3]") { REQUIRE(part_2(example_lines) == 467835L); }

TEST_CASE("part 2", "[day 3][part 2]") {
  const lines_t lines = read_lines("res/day_3_part_1.txt");
  REQUIRE(part_2(lines) == 69527306);
}
