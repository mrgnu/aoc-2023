#include "utils.hh"

#include <format>
#include <fstream>
#include <istream>

using namespace std;

namespace utils {

lines_t read_lines(const std::filesystem::path& path) {
  ifstream is(path, std::ios::in);
  if (is.bad() || is.fail()) {
    throw runtime_error(format("couldn't open file '{}'", path.string()));
  }
  lines_t lines;
  string line;
  while (getline(is, line)) {
    lines.push_back(line);
  }
  return lines;
}

std::pair<part_t, part_t> split_once(const std::string& s,
                                     const std::regex& p) {
  smatch m;
  if (!regex_search(s, m, p)) {
    throw runtime_error(format("pattern not found in '{}'", s));
  }
  const part_t first = m.prefix();
  const part_t second(m[0].second, s.cend());
  return {first, second};
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
