#include "day_5.hh"

#include <algorithm>
#include <format>
#include <optional>

#include "utils.hh"

using namespace std;
using namespace utils;

namespace {

using namespace day_5;
using day_5::id_t;

constexpr inline id_t source_start(const range_map_t& range_map) {
  return get<SOURCE_RANGE_START>(range_map);
}

constexpr inline id_t dest_start(const range_map_t& range_map) {
  return get<DESTINATION_RANGE_START>(range_map);
}

constexpr inline id_t range_len(const range_map_t& range_map) {
  return get<RANGE_LENGTH>(range_map);
}

// NOTE: range_maps is assumed to be sorted on source start
optional<range_map_t> find_range_map(const range_maps_t& range_maps,
                                     const id_t& source_id) {
  // TODO: figure out if some kind of binary search is possible
  for (const range_map_t& range_map : range_maps) {
    const id_t& start = source_start(range_map);
    const id_t end = start + range_len(range_map);
    if (source_id >= start && source_id < end) return range_map;
    if (source_id < start) break;
  }
  return {};
}

void sort_by_source_start(range_maps_t& range_map) {
  sort(range_map.begin(), range_map.end(),
       [](const range_map_t& a, const range_map_t& b) -> bool {
         return source_start(a) < source_start(b);
       });
}

ids_t parse_ids(const line_t& ids_str) {
  const parts_t id_strs = split_string(ids_str, regex("[[:blank:]]+"));
  ids_t ids;
  for (const part_t& id_str : id_strs) {
    ids.push_back(stoi(id_str));
  }
  return ids;
}

range_map_t parse_range_map(const line_t& range_str) {
  const ids_t ids = parse_ids(range_str);
  if (ids.size() != 3) {
    throw runtime_error(
        format("malformed range map: expected 3 ids, got '{}'", range_str));
  }
  return {ids.at(0), ids.at(1), ids.at(2)};
}

category_t parse_category(const lines_t& category_lines) {
  // name
  auto map_it = category_lines.cbegin();
  if (map_it->back() != ':') {
    throw runtime_error(
        format("expected name to end with ':', got '{}'", *map_it));
  }
  const string name = map_it->substr(0, map_it->size() - 1);
  ++map_it;

  // range maps
  range_maps_t range_maps;
  for (; map_it != category_lines.cend(); ++map_it) {
    const range_map_t range_map = parse_range_map(*map_it);
    range_maps.push_back(range_map);
  }

  return {name, range_maps};
}

}  // namespace

namespace day_5 {

id_t get_dest(const range_maps_t& range_maps, const id_t& source_id) {
  optional<range_map_t> range_map = find_range_map(range_maps, source_id);

  if (!range_map) return source_id;

  const int delta = source_id - source_start(*range_map);
  const id_t dest_id = dest_start(*range_map) + delta;
  return dest_id;
}

input_t parse_input(const lines_t& lines) {
  const vector<lines_t> partitions = partition_by_empty_lines(lines);

  if (partitions.size() < 2) {
    throw runtime_error(
        format("got {} partitions, expected at least 2", partitions.size()));
  }

  if (partitions.at(0).size() != 1) {
    throw runtime_error("expected separated seed line");
  }
  const line_t seed_line = partitions.at(0).front();
  const auto [name, seeds_str] = split_once(seed_line, regex(":[[:blank:]]+"));
  if (name != "seeds") {
    throw runtime_error(format("malformed seed line '{}'", seed_line));
  }
  const ids_t seeds = parse_ids(seeds_str);

  categories_t categories;
  for (auto section_it = partitions.cbegin() + 1;
       section_it != partitions.cend(); ++section_it) {
    const category_t category = parse_category(*section_it);
    categories.push_back(category);
  }

  return {seeds, categories};
}

}  // namespace day_5
