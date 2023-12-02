#include <iostream>

#include "day_2.hh"

using namespace std;
using namespace utils;
using namespace day_2;

namespace {
const lines_t example_lines{
    "Game 1: 3 blue, 4 red; 1 red, 2 green, 6 blue; 2 green",
    "Game 2: 1 blue, 2 green; 3 green, 4 blue, 1 red; 1 green, 1 blue",
    "Game 3: 8 green, 6 blue, 20 red; 5 blue, 4 red, 13 green; 5 green, 1 "
    "red",
    "Game 4: 1 green, 3 red, 6 blue; 3 green, 6 red; 3 green, 15 blue, 14 "
    "red",
    "Game 5: 6 red, 1 blue, 3 green; 2 blue, 1 red, 2 green",
};
}

result_t example_1() {
  const result_t r = part_1(example_lines);
  return r;
}

result_t example_2() {
  const result_t r = part_2(example_lines);
  return r;
}

#include "check.inl"

int main(int argc, char** argv) {
  check::check<result_t>("example 1", 8L, example_1());
  check::check<result_t>("example 2", 2286L, example_2());

  const string input_1 = argc > 1 ? argv[1] : "";
  if (!input_1.empty()) {
    const result_t expected = 2076L;
    const result_t actual = part_1(read_lines(input_1));
    check::check<result_t>("part 1", expected, actual);
  }

  if (!input_1.empty()) {
    const result_t expected = 70950L;
    const result_t actual = part_2(read_lines(input_1));
    check::check<result_t>("part 2", expected, actual);
  }

  // check::check<result_t>("example 2", 4711, example_2());

  return 0;
}
