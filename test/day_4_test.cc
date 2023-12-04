#include "../day_4.hh"

#include <catch2/catch_test_macros.hpp>

#include "../utils.hh"

using namespace utils;
using namespace day_4;

TEST_CASE("read_cards", "[day 4]") {
  const cards_t cards = read_cards(example_input);
  REQUIRE(cards.size() == 6);

  // card ID
  for (card_id_t i = 1; i <= 6; ++i) {
    const card_t& card = cards.at(i);
    const card_id_t id = get<CARD_ID>(card);
    REQUIRE(id == i);
  }

  REQUIRE(get<CARD_NUMS>(cards.at(1)) == numbers_t{41, 48, 83, 86, 17});
  REQUIRE(get<WIN_NUMS>(cards.at(6)) ==
          numbers_t{74, 77, 10, 23, 35, 67, 36, 11});
}
