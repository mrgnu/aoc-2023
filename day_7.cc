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

}  // namespace day_7
