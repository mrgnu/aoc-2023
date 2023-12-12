#include "day_7.hh"

#include <format>

using namespace std;
using namespace utils;

namespace {

using namespace day_7;

game_t parse_game(const line_t& line) {
  const auto& [hand_str, bid_str] = split_once(line, regex("[[:blank:]]+"));
  if (hand_str.length() != 5) {
    throw runtime_error(format("invalid hand: {}", hand_str));
  }
  const hand_t hand{hand_str.at(0), hand_str.at(1), hand_str.at(2),
                    hand_str.at(3), hand_str.at(4)};

  const bid_t bid = stoi(bid_str);

  return {hand, bid};
}

enum hand_type_t {
  HIGH_CARD = 0,
  ONE_PAIR = 1,
  TWO_PAIR = 2,
  THREE_OF_A_KIND = 3,
  FULL_HOUSE = 4,
  FOUR_OF_A_KIND = 5,
  FIVE_OF_A_KIND = 6,
};

hand_type_t get_hand_type(const hand_t& hand) {
  using count_t = unsigned char;
  map<card_t, count_t> cards;
  for (const card_t c : hand) {
    auto it = cards.find(c);
    if (it == cards.end()) {
      cards[c] = 1;
    } else {
      ++(it->second);
    }
  }

  switch (cards.size()) {
    case 1:
      return FIVE_OF_A_KIND;
    case 2:
      // either full house or four of a kind
      return (cards.cbegin()->second == 1 || cards.cbegin()->second == 4)
                 ? FOUR_OF_A_KIND
                 : FULL_HOUSE;
    case 3:
      // either two pairs or three of a kind
      return (cards.cbegin()->second == 2 || next(cards.cbegin())->second == 2)
                 ? TWO_PAIR
                 : THREE_OF_A_KIND;
    case 4:
      return ONE_PAIR;
    case 5:
      return HIGH_CARD;

    default:
      throw logic_error("something is wrong");
  }
}

using val_t = int;

constexpr inline val_t get_card_value(const card_t& c) {
  switch (c) {
    case 'A':
      return 14;
    case 'K':
      return 13;
    case 'Q':
      return 12;
    case 'J':
      return 11;
    case 'T':
      return 10;
    default:
      return c - '0';
  }
}

bool hand_comp(const hand_t& a, const hand_t& b) {
  const hand_type_t at = get_hand_type(a);
  const hand_type_t bt = get_hand_type(b);

  if (at != bt) {
    return at < bt;
  }

  for (hand_t::size_type i = 0; i < a.size(); ++i) {
    const val_t av = get_card_value(a[i]);
    const val_t bv = get_card_value(b[i]);
    if (av != bv) return av < bv;
  }
  return false;
}

}  // namespace

namespace day_7 {

games_t parse_input(const lines_t& lines) {
  games_t games;
  games.reserve(lines.size());
  for (const line_t& line : lines) {
    games.push_back(parse_game(line));
  }
  return games;
}

games_t sort_games(const games_t& games) {
  games_t sorted(games.cbegin(), games.cend());
  sort(sorted.begin(), sorted.end(), [](const game_t& a, const game_t& b) {
    return hand_comp(a.first, b.first);
  });
  return sorted;
}

}  // namespace day_7
