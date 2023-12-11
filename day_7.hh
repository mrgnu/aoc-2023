#pragma once

#include "utils.hh"

namespace day_7 {

const utils::lines_t example_input{
    // clang-format off
  "32T3K 765",
  "T55J5 684",
  "KK677 28",
  "KTJJT 220",
  "QQQJA 483",
    // clang-format on
};

using bid_t = unsigned;
using card_t = std::string::value_type;
using hand_t = std::array<card_t, 5>;
using game_t = std::pair<hand_t, bid_t>;
using games_t = std::vector<game_t>;

games_t parse_input(const utils::lines_t& lines);

}  // namespace day_7
