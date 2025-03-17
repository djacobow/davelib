#pragma once

#include <string>

namespace dave::hex {

std::string bin2hex(const void *p, size_t l);
std::string bin2hex(const std::string &s);
std::string bin2printable(const void *p, size_t l);
std::string bin2hex_canonical(const std::string &s);
std::string bin2hex_canonical(const void *p, size_t l);

} // namespace dave::hex

