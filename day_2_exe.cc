#include <iostream>

#include "day_2.hh"

using namespace std;
using namespace utils;
using namespace day_2;

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
