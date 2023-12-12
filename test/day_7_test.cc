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

TEST_CASE("sort_games", "[day 7]") {
  const games_t games = parse_input(example_input);
  const games_t sorted = sort_games(games);
  REQUIRE(sorted == games_t{
                        game_t{hand_t{'3', '2', 'T', '3', 'K'}, 765},
                        game_t{hand_t{'K', 'T', 'J', 'J', 'T'}, 220},
                        game_t{hand_t{'K', 'K', '6', '7', '7'}, 28},
                        game_t{hand_t{'T', '5', '5', 'J', '5'}, 684},
                        game_t{hand_t{'Q', 'Q', 'Q', 'J', 'A'}, 483},
                    });
}

TEST_CASE("wild_sort_games", "[day 7]") {
  const games_t games = parse_input(example_input);
  const games_t sorted = wild_sort_games(games);
  REQUIRE(sorted == games_t{
                        game_t{hand_t{'3', '2', 'T', '3', 'K'}, 765},
                        game_t{hand_t{'K', 'K', '6', '7', '7'}, 28},
                        game_t{hand_t{'T', '5', '5', 'J', '5'}, 684},
                        game_t{hand_t{'Q', 'Q', 'Q', 'J', 'A'}, 483},
                        game_t{hand_t{'K', 'T', 'J', 'J', 'T'}, 220},
                    });
}

TEST_CASE("example 1", "[day 7]") { REQUIRE(part_1(example_input) == 6440); }

TEST_CASE("part 1", "[day 7]") {
  REQUIRE(part_1(utils::read_lines("res/day_7_part_1.txt")) == 250120186);
}
