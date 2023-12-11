#include "day_5.hh"

#include <algorithm>
#include <cmath>
#include <format>
#include <numeric>
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
  using i_t = long;
  i_t left = 0;
  i_t right = range_maps.size() - 1;
  while (left <= right) {
    const i_t mid = (left + right) / 2;
    const range_map_t& range_map = range_maps.at(mid);
    const id_t& start = source_start(range_map);
    const id_t end = start + range_len(range_map);

    if (source_id < start) {
      right = mid - 1;
      continue;
    }

    if (source_id >= end) {
      left = mid + 1;
      continue;
    }

    return range_map;
  }
  return {};
}

optional<range_map_t> find_next_range_map(const range_maps_t& range_maps,
                                          const id_t& id) {
  for (const range_map_t& range_map : range_maps) {
    const id_t& start = get<SOURCE_RANGE_START>(range_map);
    if (id < start) {
      return range_map;
    }
  }
  return {};
}

template <range_map_tuple_t sorting>
void sort_by(range_maps_t& range_maps) {
  sort(range_maps.begin(), range_maps.end(),
       [](const range_map_t& a, const range_map_t& b) -> bool {
         return get<sorting>(a) < get<sorting>(b);
       });
}

void sort_by_source_start(range_maps_t& range_maps) {
  sort_by<SOURCE_RANGE_START>(range_maps);
}

ids_t parse_ids(const line_t& ids_str) {
  const parts_t id_strs = split_string(ids_str, regex("[[:blank:]]+"));
  ids_t ids;
  for (const part_t& id_str : id_strs) {
    ids.push_back(stol(id_str));
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

  // NOTE: sort on source start
  sort_by_source_start(range_maps);

  return {name, range_maps};
}

id_t remap_seed(const categories_t& categories, const id_t seed_id) {
  id_t id = seed_id;
  for (const category_t& category : categories) {
    id = get_dest(category.second, id);
  }
  return id;
}

// traverse categories map from start to finish, shrinking the range
// length to produce the range using the same path (aka same set of
// range maps).
range_map_t collect_consecutive_range(const categories_t& categories,
                                      const id_t seed_range_start,
                                      id_t seed_range_len) {
  id_t id = seed_range_start;
  id_t len = seed_range_len;
  for (const category_t& category : categories) {
    const range_maps_t& range_maps = category.second;
    optional<range_map_t> range_map = find_range_map(range_maps, id);

    // this step hit a range map, figure out how many ids hit it
    if (range_map) {
      const long delta = id - source_start(*range_map);
      const id_t dest_id = dest_start(*range_map) + delta;
      id = dest_id;
      len = min(len, range_len(*range_map) - delta);
      continue;
    }

    // this step didn't hit a range map, figure out distance to the
    // next larger one
    optional<range_map_t> next_map = find_next_range_map(range_maps, id);

    // no next means all IDs >= source map to identity - keep old len and id
    if (!next_map) {
      continue;
    }

    // len is capped to distance from source ID to start of next range map
    len = min(len, source_start(*next_map) - id);
  }

  return {id, seed_range_start, len};
}

range_maps_t collect_consecutive_ranges(const categories_t& categories,
                                        const id_t seed_range_start,
                                        id_t seed_range_len) {
  const id_t seed_range_end = seed_range_start + seed_range_len;
  range_maps_t out_maps;

  id_t start = seed_range_start;
  id_t len = seed_range_len;
  while (len > 0) {
    const range_map_t con_range =
        collect_consecutive_range(categories, start, len);
    const id_t con_len = range_len(con_range);
    start += con_len;
    len -= con_len;
    out_maps.push_back(con_range);
  }

  return out_maps;
}

id_t find_min_location_from_ranges(const categories_t& categories,
                                   const ids_t& seed_ranges) {
  id_t min_dist_seed_id = 0;
  id_t min_location_id = numeric_limits<id_t>::max();
  for (ids_t::size_type i = 0; i < seed_ranges.size(); i += 2) {
    const id_t seed_range_start = seed_ranges.at(i + 0);
    const id_t seed_range_len = seed_ranges.at(i + 1);
    range_maps_t range_maps = collect_consecutive_ranges(
        categories, seed_range_start, seed_range_len);
    sort_by<DESTINATION_RANGE_START>(range_maps);
    if (dest_start(range_maps.front()) < min_location_id) {
      min_dist_seed_id = source_start(range_maps.front());
      min_location_id = dest_start(range_maps.front());
    }
  }
  return min_location_id;
}

}  // namespace

namespace day_5 {

input_t parse_input(const utils::lines_t& lines) {
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

id_t get_dest(const range_maps_t& range_maps, const id_t& source_id) {
  optional<range_map_t> range_map = find_range_map(range_maps, source_id);

  if (!range_map) return source_id;

  const long delta = source_id - source_start(*range_map);
  const id_t dest_id = dest_start(*range_map) + delta;
  return dest_id;
}

id_t part_1(const lines_t& lines) {
  const input_t input = parse_input(lines);
  const ids_t seed_ids = input.first;
  const categories_t& cats = input.second;

  ids_t location_ids;
  transform(seed_ids.cbegin(), seed_ids.cend(), back_inserter(location_ids),
            [&cats](const id_t& id) -> id_t { return remap_seed(cats, id); });

  sort(location_ids.begin(), location_ids.end());
  return location_ids.front();
}

id_t part_2(const lines_t& lines) {
  const input_t input = parse_input(lines);
  const ids_t seed_ranges = input.first;
  const categories_t& categories = input.second;

  const id_t location = find_min_location_from_ranges(categories, seed_ranges);
  return location;
}

}  // namespace day_5
