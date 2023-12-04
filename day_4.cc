#include "day_4.hh"

#include <format>
#include <ranges>
#include <regex>

using namespace std;
using namespace utils;

namespace {

using namespace day_4;

card_id_t parse_card_id(const part_t& card_spec) {
  static regex card_re("Card[[:blank:]]+([[:digit:]]+)");
  smatch m;
  if (!regex_match(card_spec, m, card_re)) {
    throw runtime_error(format("failed to parse card spec '{}'", card_spec));
  }

  return stoi(m[1]);
}

numbers_t parse_nums(const part_t& nums_spec) {
  const parts_t parts = split_string(nums_spec, regex("[[:blank:]]+"));
  auto range =
      parts | views::transform([](const part_t& n) { return stoi(n); });
  numbers_t nums;
  copy(range.begin(), range.end(), inserter(nums, nums.begin()));
  return nums;
}

card_t read_line(const line_t& line) {
  const auto [card_spec, all_nums_spec] =
      split_once(line, regex(":[[:blank:]]+"));

  const card_id_t card_id = parse_card_id(card_spec);

  const auto [nums_spec, wins_spec] =
      split_once(all_nums_spec, regex("[[:blank:]]+\\|[[:blank:]]+"));
  const numbers_t nums = parse_nums(nums_spec);
  const numbers_t wins = parse_nums(wins_spec);

  return {card_id, nums, wins};
}

}  // namespace

namespace day_4 {

cards_t read_cards(const lines_t& lines) {
  auto range = lines | views::transform(read_line) |
               views::transform([](const card_t& card) {
                 const card_id_t& id = get<CARD_ID>(card);
                 return cards_t::value_type{id, card};
               });
  cards_t cards;
  cards.insert(range.begin(), range.end());
  return cards;
}

}  // namespace day_4
