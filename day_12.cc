#include "day_12.hh"

#include <cmath>
#include <ranges>
#include <set>

namespace {

using namespace day_12;

nums_t read_nums(const utils::line_t& nums_str) {
  auto v = utils::split_string(nums_str, std::regex(",")) |
           std::views::transform([](const std::string& s) { return stoi(s); });
  nums_t nums;
  std::copy(v.begin(), v.end(), std::back_inserter(nums));
  return nums;
}

utils::parts_t trim(const utils::parts_t& parts) {
  utils::parts_t trimmed;
  for (const auto& p : parts) {
    if (p.empty()) continue;
    trimmed.push_back(p);
  }
  return trimmed;
}

bool is_valid(const utils::line_t& l, const nums_t& nums) {
  // skip until first broken range
  const char* ls = l.c_str();
  while (*ls == '.') ++ls;
  if (!*ls) return nums.empty();

  nums_t::size_type num_i = 0;
  while (*ls) {
    if (num_i >= nums.size()) return false;

    num_t bc = 0;
    while (*ls == '#') {
      ++ls;
      ++bc;
    }
    if (bc != nums[num_i]) return false;
    while (*ls == '.') ++ls;
    ++num_i;
  }
  return num_i == nums.size();
}

arr_count_t count_arrs(const utils::line_t& line) {
  const auto [pat, nums_str] =
      utils::split_once(line, std::regex("[[:blank:]]+"));

  const nums_t nums = read_nums(nums_str);

  using pos_t = utils::line_t::size_type;
  // indices of unknown springs
  std::set<pos_t> ui;
  for (pos_t i = 0; i < line.size(); ++i) {
    if (line[i] == '?') ui.insert(i);
  }

  arr_count_t valid_count = 0;
  const arr_count_t n = std::pow(2, ui.size());
  for (arr_count_t a = 0; a < n; ++a) {
    // a is a bit mask with state for all unknowns
    arr_count_t bt = a;

    utils::line_t l = pat;
    for (const pos_t& p : ui) {
      l[p] = (bt & 1) ? '.' : '#';
      bt >>= 1;
    }
    // l now has states applied
    if (is_valid(l, nums)) ++valid_count;
  }

  return valid_count;
}

}  // namespace

namespace day_12 {

bool is_valid(const utils::line_t& l, const nums_t& nums) {
  return ::is_valid(l, nums);
}

}  // namespace day_12
