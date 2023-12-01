#include <iostream>
#include <map>
#include <numeric>
#include <ranges>

#include "utils.hh"

using namespace std;
using namespace utils;

using char_t = line_t::value_type;

int digit_to_int(const char_t c) { return c - '0'; }

int get_calibration_value(const line_t& line) {
  auto digit = [](char_t c) { return isdigit(c); };
  auto r = line | views::filter(digit) | views::transform(digit_to_int);
  char_t first = r.front();
  char_t last = r.back();
  return 10 * first + last;
}

// replaces word digits with regular digits
// NOTE: drops parts of string that are not digits
line_t replace_word_digits(const line_t& input) {
  static map<line_t, int> word_digit_map{
      {
          "one",
          1,
      },
      {
          "two",
          2,
      },
      {
          "three",
          3,
      },
      {
          "four",
          4,
      },
      {
          "five",
          5,
      },
      {
          "six",
          6,
      },
      {
          "seven",
          7,
      },
      {
          "eight",
          8,
      },
      {
          "nine",
          9,
      },
  };

  string replaced;
  for (auto it = input.cbegin(); it != input.cend(); ++it) {
    const string_view s(it, input.cend());

    // string contains raw digit
    if (isdigit(s[0])) {
      replaced += s[0];
      continue;
    }

    // string contains some word digit
    for (const auto& word_digit : word_digit_map) {
      const auto& word = word_digit.first;
      const auto& digit = word_digit.second;
      if (s.starts_with(word)) {
        replaced += to_string(digit);
        // NOTE: overlapping digit words still count as both digits
        break;
      }
    }

    // no match - ignore this char
  }

  return replaced;
}

int part_1(const lines_t& lines) {
  const auto vs =
      lines | views::transform(get_calibration_value) | views::common;
  return accumulate(vs.begin(), vs.end(), 0);
}

int example_1() {
  return part_1({
      "1abc2",
      "pqr3stu8vwx",
      "a1b2c3d4e5f",
      "treb7uchet",
  });
}

int part_2(const lines_t& lines) {
  const auto vs = lines | views::transform(replace_word_digits) |
                  views::transform(get_calibration_value) | views::common;
  return accumulate(vs.begin(), vs.end(), 0);
}

int example_2() {
  return part_2({
      "two1nine",
      "eightwothree",
      "abcone2threexyz",
      "xtwone3four",
      "4nineeightseven2",
      "zoneight234",
      "7pqrstsixteen",
  });
}

#include "check.inl"

int main(int argc, char** argv) {
  const lines_t lines = read_lines("res/day_1_part_1.txt");
  bool success = true;
  success &= check::check("example 1", 142, example_1());
  success &= check::check("example 2", 281, example_2());
  success &= check::check("part 1", 55538, part_1(lines));
  success &= check::check("part 2", 54875, part_2(lines));

  return success ? 0 : 1;
}
