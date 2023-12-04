#include "day_4.hh"

#include <cmath>
#include <format>
#include <numeric>
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

result_t winning_number_count(const card_t& card) {
  const numbers_t& nums = get<CARD_NUMS>(card);
  const numbers_t& wins = get<WIN_NUMS>(card);
  numbers_t common;
  set_intersection(nums.cbegin(), nums.cend(), wins.cbegin(), wins.cend(),
                   inserter(common, common.begin()));
  return common.size();
}

using card_count_t = result_t;
using card_count_map_t = map<card_id_t, card_count_t>;

card_count_map_t get_final_card_counts(const cards_t& cards) {
  // NOTE: map is sorted
  auto card_id_range = cards | views::keys;

  card_count_map_t card_counts;

  // init card counts
  for (const card_id_t& card_id : card_id_range) {
    card_counts[card_id] = 1;
  }

  // update card counts
  for (const card_id_t& card_id : card_id_range) {
    const result_t win_count = winning_number_count(cards.at(card_id));

    const card_count_t card_count = card_counts.at(card_id);
    for (card_id_t win_id = card_id + 1; win_id <= card_id + win_count;
         ++win_id) {
      card_counts[win_id] += card_count;
    }
  }

  return card_counts;
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

result_t part_1(const utils::lines_t& lines) {
  const cards_t cards = read_cards(lines);
  auto range = cards |
               views::transform([](const cards_t::value_type& p) -> card_t {
                 return p.second;
               }) |
               views::transform(winning_number_count) |
               // get points for number of common digits - aka 2^(count - 1)
               views::transform([](const result_t& n) -> result_t {
                 return pow(2, static_cast<long>(n) - 1);
               });
  const result_t points = accumulate(range.begin(), range.end(), 0);
  return points;
}

result_t part_2(const utils::lines_t& lines) {
  const cards_t cards = read_cards(lines);
  const card_count_map_t card_counts = get_final_card_counts(cards);
  auto counts = card_counts | views::values;
  const result_t count = accumulate(counts.begin(), counts.end(), 0);
  return count;
}

}  // namespace day_4
