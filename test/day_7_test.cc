#include "../day_7.hh"

#include <catch2/catch_test_macros.hpp>

#include "../utils.hh"

using namespace day_7;

TEST_CASE("parse_input", "[day 7]") {
  REQUIRE(parse_input(example_input) ==
          games_t{
              game_t{hand_t{'3', '2', 'T', '3', 'K'}, 765},
              game_t{hand_t{'T', '5', '5', 'J', '5'}, 684},
              game_t{hand_t{'K', 'K', '6', '7', '7'}, 28},
              game_t{hand_t{'K', 'T', 'J', 'J', 'T'}, 220},
              game_t{hand_t{'Q', 'Q', 'Q', 'J', 'A'}, 483},
          });
}
