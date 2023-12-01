#pragma once

#include <filesystem>
#include <string>
#include <vector>

namespace utils {

using line_t = std::string;
using lines_t = std::vector<line_t>;

lines_t read_lines(const std::filesystem::path& path);
}  // namespace utils
