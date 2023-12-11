#pragma once

#include <tuple>
#include <vector>

#include "utils.hh"

namespace day_5 {

const utils::lines_t example_lines{
    "seeds: 79 14 55 13",
    "",
    "seed-to-soil map:",
    "50 98 2",
    "52 50 48",
    "",
    "soil-to-fertilizer map:",
    "0 15 37",
    "37 52 2",
    "39 0 15",
    "",
    "fertilizer-to-water map:",
    "49 53 8",
    "0 11 42",
    "42 0 7",
    "57 7 4",
    "",
    "water-to-light map:",
    "88 18 7",
    "18 25 70",
    "",
    "light-to-temperature map:",
    "45 77 23",
    "81 45 19",
    "68 64 13",
    "",
    "temperature-to-humidity map:",
    "0 69 1",
    "1 0 69",
    "",
    "humidity-to-location map:",
    "60 56 37",
    "56 93 4",
};

enum range_map_tuple_t {
  DESTINATION_RANGE_START = 0,
  SOURCE_RANGE_START = 1,
  RANGE_LENGTH = 2,
};

using id_t = long;
using ids_t = std::vector<id_t>;
using range_map_t = std::tuple<id_t, id_t, id_t>;
using range_maps_t = std::vector<range_map_t>;

// a category is a named set of range maps, used to translate from one type of
// id to another - e.g. all seed-to-soil maps
using category_t = std::pair<std::string, range_maps_t>;
using categories_t = std::vector<category_t>;
// pair of seeds and categories
using input_t = std::pair<ids_t, categories_t>;

// convert source ID to destination ID
// NOTE: range_maps is assumed to be sorted on source start
id_t get_dest(const range_maps_t& range_maps, const id_t& source_id);

input_t parse_input(const utils::lines_t& lines);

id_t part_1(const utils::lines_t& lines);

id_t part_2(const utils::lines_t& lines);

}  // namespace day_5
