// -*- mode: c++ -*-

#include "lcm.hh"

namespace utils {
template <typename T>
T lcm(const std::vector<T> vs) {
  if (vs.size() < 2) return 1;
  return std::reduce(std::next(vs.cbegin()), vs.cend(), vs.front(),
                     std::lcm<T, T>);
}
}  // namespace utils
