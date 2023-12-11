#include "../day_6.hh"

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

template <typename A, typename B>
ostream& operator<<(ostream& os, const pair<A, B>& p) {
  os << "[" << p.first << "; " << p.second << "]";
  return os;
}

}  // namespace std

using namespace utils;
using namespace day_6;

TEST_CASE("parse_lines", "[day 6]") {
  REQUIRE(parse_lines(example_lines) == races_t{
                                            race_t{7, 9},
                                            race_t{15, 40},
                                            race_t{30, 200},
                                        });
}

TEST_CASE("get_winning_times", "[day 6]") {
  REQUIRE(get_winning_times(race_t{7, 9}) == std::vector<result_t>{2, 3, 4, 5});
}

TEST_CASE("example 1", "[day 6]") { REQUIRE(part_1(example_lines) == 288); }

TEST_CASE("part 1", "[day 6]") {
  REQUIRE(part_1(read_lines("res/day_6_part_1.txt")) == 440000);
}
