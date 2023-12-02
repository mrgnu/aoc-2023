// -*- mode: c++ -*-

namespace check {

template <typename T>
bool check(const std::string& name, const T& expected, const T& actual) {
  std::cout << name << ":" << std::endl;
  std::cout << "'" << actual << "'" << std::endl;
  if (expected == actual) return true;
  std::cerr << name << " FAILED, expected" << std::endl;
  std::cerr << "'" << expected << "'" << std::endl;
  return false;
}

}  // namespace check
