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

using count_t = unsigned char;
using card_counts_t = map<card_t, count_t>;

card_counts_t get_card_counts(const hand_t& hand) {
  card_counts_t card_counts;
  for (const card_t c : hand) {
    auto it = card_counts.find(c);
    if (it == card_counts.end()) {
      card_counts[c] = 1;
    } else {
      ++(it->second);
    }
  }
  return card_counts;
}

hand_type_t get_hand_type(const card_counts_t& card_counts) {
  switch (card_counts.size()) {
    case 1:
      return FIVE_OF_A_KIND;
    case 2:
      // either full house or four of a kind
      return (card_counts.cbegin()->second == 1 ||
              card_counts.cbegin()->second == 4)
                 ? FOUR_OF_A_KIND
                 : FULL_HOUSE;
    case 3:
      // either two pairs or three of a kind
      return (card_counts.cbegin()->second == 2 ||
              next(card_counts.cbegin())->second == 2)
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

hand_type_t get_hand_type(const hand_t& hand) {
  return get_hand_type(get_card_counts(hand));
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

card_counts_t get_wild_card_counts(const hand_t& hand) {
  card_counts_t counts = get_card_counts(hand);
  auto wild_it = counts.find('J');

  // no jokers
  if (wild_it == counts.cend()) return counts;

  // only jokers
  if (counts.size() == 1) return counts;

  // promote jokers to whatever card has most occurances, excluding jokers

  // unique cards in hand, ordered by count, decreasing
  vector<card_t> sorted;
  for (const auto& p : counts) sorted.push_back(p.first);
  sort(sorted.begin(), sorted.end(),
       [&counts](const card_t& a, const card_t& b) -> bool {
         // NOTE: reverse condition, we want most occurences first
         return counts.at(a) > counts.at(b);
       });

  // *it will represent unique card with most occurences, excluding joker
  auto it = sorted.begin();
  if (*it == 'J') ++it;

  const count_t j_count = wild_it->second;
  counts.erase(wild_it);
  counts[*it] += j_count;

  return counts;
}

constexpr inline val_t get_wild_card_value(const card_t& c) {
  return c == 'J' ? 1 : get_card_value(c);
}

bool wild_hand_comp(const hand_t& a, const hand_t& b) {
  const hand_type_t at = get_hand_type(get_wild_card_counts(a));
  const hand_type_t bt = get_hand_type(get_wild_card_counts(b));

  if (at != bt) {
    return at < bt;
  }

  for (hand_t::size_type i = 0; i < a.size(); ++i) {
    const val_t av = get_wild_card_value(a[i]);
    const val_t bv = get_wild_card_value(b[i]);
    if (av != bv) return av < bv;
  }
  return false;
}

winnings_t compute_winnings(const games_t& sorted) {
  winnings_t total_winnings = 0;
  for (auto it = sorted.cbegin(); it != sorted.cend(); ++it) {
    const game_t& game = *it;
    const int rank = distance(sorted.cbegin(), it) + 1;
    const bid_t& bid = game.second;
    const winnings_t winnings = bid * rank;
    total_winnings += winnings;
  }
  return total_winnings;
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

games_t wild_sort_games(const games_t& games) {
  games_t sorted(games.cbegin(), games.cend());
  sort(sorted.begin(), sorted.end(), [](const game_t& a, const game_t& b) {
    return wild_hand_comp(a.first, b.first);
  });
  return sorted;
}

winnings_t part_1(const lines_t& lines) {
  const games_t games = parse_input(lines);
  const games_t sorted = sort_games(games);
  return compute_winnings(sorted);
}

winnings_t part_2(const lines_t& lines) {
  const games_t games = parse_input(lines);
  const games_t sorted = wild_sort_games(games);
  return compute_winnings(sorted);
}

}  // namespace day_7
