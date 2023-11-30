#pragma once

#include <filesystem>
#include <string>
#include <vector>

namespace utils {

using lines_t = std::vector<std::string>;

lines_t read_lines(const std::filesystem::path& path);
}  // namespace utils
