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

class ColorTuple_t {
    public:
    ColorTuple_t() :
        fg_(Color_e::nochange),
        bg_(Color_e::nochange),
        m_(ColorMode_e::nochange) {}

    Color_e fg_;
    Color_e bg_;
    ColorMode_e m_;
};

constexpr std::string colorModeOn(const ColorTuple_t &ct);
constexpr std::string colorReset();
[[maybe_unused]] std::string &colorModeWrap(const ColorTuple_t &ct, std::string &s);

}
