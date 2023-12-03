// -*- mode: c++ -*-

namespace utils {

template <typename K, typename T>
constexpr inline T get_or(const std::map<K, T>& m, const K& k,
                          const T fallback) {
  const auto it = m.find(k);
  return it == m.cend() ? fallback : it->second;
}

}  // namespace utils
