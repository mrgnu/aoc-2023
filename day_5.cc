#include "day_5.hh"

#include <algorithm>
#include <optional>

using namespace std;

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

}  // namespace

namespace day_5 {

id_t get_dest(const range_maps_t& range_maps, const id_t& source_id) {
  optional<range_map_t> range_map = find_range_map(range_maps, source_id);

  if (!range_map) return source_id;

  const int delta = source_id - source_start(*range_map);
  const id_t dest_id = dest_start(*range_map) + delta;
  return dest_id;
}

}  // namespace day_5
