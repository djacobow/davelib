#include <string>

#include "dave/inc/log/colorize.h"
#include "dave/inc/log/colors.h"
#include "dave/inc/log/levels.h"

namespace dave::log {

auto Colorize(Level_e l, std::string &os) -> std::string & {
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

}  // namespace dave::log
