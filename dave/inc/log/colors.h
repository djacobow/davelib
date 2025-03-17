#pragma once

#include <string>

namespace dave::log {

enum class Color_e {
    black = 0,
    red,
    green,
    yellow,
    blue,
    magenta,
    cyan,
    white,
    nochange,
};

enum class ColorMode_e {
    normal = 0,
    bold,
    dim,
    italic,
    underline,
    blink,
    fastblink,
    reverse,
    hide,
    strikethrough,
    nochange,
};

struct ColorTuple_t {
    Color_e fg_{Color_e::nochange};
    Color_e bg_{Color_e::nochange};
    ColorMode_e m_{ColorMode_e::nochange};
};

constexpr std::string colorModeOn(const ColorTuple_t &ct);
constexpr std::string colorReset();
[[maybe_unused]] std::string &colorModeWrap(const ColorTuple_t &ct, std::string &s);

} // namespace dave::log
