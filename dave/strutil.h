#pragma once

#include <cstdint>
#include <string>
#include <vector>

namespace dave::str {

extern const std::string newline;

auto split(const std::string &s, const std::string &delim) -> std::vector<std::string>;
auto stringOrSpace(bool skip, const std::string &s) -> std::string;
auto join(const std::vector<std::string> &joinees, const std::string &joiner) -> std::string;
auto box(const std::string &title, const std::string &contents, uint32_t width = 60) -> std::string;
auto box(const std::string &title, const std::vector<std::string> &lines, uint32_t width = 60) -> std::string;
auto repeat(const std::string &s, uint32_t n) -> std::string;
auto split_white(const std::string &s) -> std::vector<std::string>;
auto wrap(const std::string &s, uint32_t max_w) -> std::vector<std::string>;

} // namespace dave::str
