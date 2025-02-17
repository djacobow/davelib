#include <unistd.h>

#include "dlog/colorize.h"
#include "dlog/colors.h"

namespace dlog {

std::string &Colorize(Level_e l, std::string &os) {
    ColorTuple_t ct;
    static const auto important   = LevelMask_c().AtOrAbove(Level_e::notice);
    static const auto unimportant = LevelMask_c().AtOrBelow(Level_e::debug);

    if (important.Contains(l)) {
        ct.m_ = ColorMode_e::bold;
    } else if (unimportant.Contains(l)) {
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
            ct.fg_ = Color_e::white;
            ct.bg_ = Color_e::red;
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

