#pragma once

#include <filesystem>
#include <regex>
#include <string>
#include <vector>

namespace utils {

using line_t = std::string;
using lines_t = std::vector<line_t>;

lines_t read_lines(const std::filesystem::path& path);

using part_t = std::string;
using parts_t = std::vector<part_t>;

std::pair<part_t, part_t> split_once(const std::string& s, const std::regex& p);

parts_t split_string(const std::string& s, const std::regex& p);

}  // namespace utils
