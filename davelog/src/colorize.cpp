#include <unistd.h>

#include "davelog/colorize.h"
#include "davelog/colors.h"

namespace dave::log {

std::string &Colorize(Level_e l, std::string &os) {
    LevelMask_c important;
    important.AtOrAbove(Level_e::notice);
    LevelMask_c unimportant;
    unimportant.AtOrBelow(Level_e::debug);

    auto mask = LevelToMask(l);

    ColorTuple_t ct;

    if (mask & important.GetMask()) {
        ct.m_ = ColorMode_e::bold;
    } else if (mask & unimportant.GetMask()) {
        ct.m_ = ColorMode_e::dim;
    } 

    switch (l) {
        case Level_e::warning:
            ct.fg_ = Color_e::yellow;
            break;
        case Level_e::error:
            ct.fg_ = Color_e::red;
            break;
        case Level_e::fatal:
            ct.fg_ = Color_e::red;
            ct.bg_ = Color_e::white;
            break;
        case Level_e::notice:
            ct.fg_ = Color_e::cyan;
        default:
            break;
    }

    colorModeWrap(ct, os);
    return os;
}

}

