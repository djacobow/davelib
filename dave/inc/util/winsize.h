#pragma once

#include <cstdint>

#include "dave/inc/err/valueor.hpp"

namespace dave::util {

struct TerminalDimensions_t {
    uint32_t width;
    uint32_t height;
};

dave::err::ValueOr_c<TerminalDimensions_t> GetTerminalDimensions();

} // namespace dave::util

