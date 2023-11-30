#include "utils.hh"

#include <fstream>
#include <istream>

using namespace std;

namespace utils {

lines_t read_lines(const std::filesystem::path& path) {
  ifstream is(path, std::ios::in);
  lines_t lines;
  string line;
  while (getline(is, line)) {
    lines.push_back(line);
  }
  return lines;
}
}  // namespace utils
