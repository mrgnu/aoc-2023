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

parts_t split_string(const std::string& s, const std::regex& p) {
  std::sregex_token_iterator it(s.cbegin(), s.cend(), p, -1);
  std::sregex_token_iterator end;
  parts_t parts;
  for (; it != end; ++it) {
    parts.push_back(*it);
  }
  return parts;
}

}  // namespace utils
