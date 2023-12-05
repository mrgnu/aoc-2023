#pragma once

#include <tuple>
#include <vector>

namespace day_5 {

enum range_map_tuple_t {
  DESTINATION_RANGE_START = 0,
  SOURCE_RANGE_START = 1,
  RANGE_LENGTH = 2,
};

using id_t = int;
using range_map_t = std::tuple<id_t, id_t, id_t>;

using range_maps_t = std::vector<range_map_t>;

// convert source ID to destination ID
// NOTE: range_maps is assumed to be sorted on source start
id_t get_dest(const range_maps_t& range_maps, const id_t& source_id);

}  // namespace day_5
