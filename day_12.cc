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

using str_ptr_t = utils::line_t::const_pointer;
using num_it_t = nums_t::const_iterator;

// checks that p can fit n broken springs, and that there isn't another broken
// spring after.
bool can_fit(str_ptr_t p, const num_t n) {
  for (size_t i = 0; i < n; ++i) {
    if (p[i] != '#' && p[i] != '?') return false;
  }
  return p[n] != '#';
}

arr_count_t count_arrs_m(str_ptr_t p, num_it_t num, num_it_t num_end);

arr_count_t count_arrs_r(str_ptr_t p, num_it_t num, num_it_t num_end) {
  arr_count_t c = 0;

  {
    if (num == num_end) {
      // if no nums are left, match if no broken springs remain
      while (*p && *p != '#') ++p;
      return *p ? 0 : 1;
    }

    // skip forward to next broken or unknown section
    while (*p == '.') ++p;

    // eol with nums remaining - no match
    if (!*p) {
      return 0;
    }

    const num_t this_num = *num;
    if (can_fit(p, this_num)) {
      // NOTE: can_fit allows fit on eol as well as non-broken spring
      str_ptr_t np = p + this_num;
      if (*np) ++np;

      // start of p fits first remaining num broken springs - continue matching
      c += count_arrs_m(np, std::next(num), num_end);
    }

    if (*p == '#') {
      // actual broken spring - no more tries from here
      return c;
    }
  }

  // figure out start of next possible run
  if (*p == '#') {
    // if start was on a broken spring, skip forward until not
    while (*p == '#') ++p;
  }
  if (*p) ++p;

  c += count_arrs_m(p, num, num_end);
  return c;
}

// memoized version of count_arrs_r
arr_count_t count_arrs_m(str_ptr_t p, num_it_t num, num_it_t num_end) {
  using mem_ent_t = std::pair<std::string, nums_t>;
  static std::map<mem_ent_t, arr_count_t> s_mem;

  const mem_ent_t e{p, nums_t{num, num_end}};
  auto it = s_mem.find(e);
  if (it != s_mem.end()) {
    return it->second;
  }

  const arr_count_t c = count_arrs_r(p, num, num_end);
  s_mem[e] = c;
  return c;
}

arr_count_t count_arrs(const utils::line_t& line) {
  const auto [pat, nums_str] =
      utils::split_once(line, std::regex("[[:blank:]]+"));

  const nums_t nums = read_nums(nums_str);

  return count_arrs_m(pat.c_str(), nums.cbegin(), nums.cend());
}

}  // namespace

namespace day_12 {

bool is_valid(const utils::line_t& l, const nums_t& nums) {
  return ::is_valid(l, nums);
}

arr_count_t part_1(const utils::lines_t& lines) {
  arr_count_t acc = 0;
  for (const utils::line_t& line : lines) {
    acc += count_arrs(line);
  }
  return acc;
}

}  // namespace day_12
