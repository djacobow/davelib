#include "davelog/levels.h"
#include "davelog/enum_range.h"

#include <vector>

namespace dave::log {

EH_IMPL_ENUM_STRINGIFIER(get_Level_e_str, Level_e, LOG_LEVELS);


LevelMask_c::LevelMask_c() : mask_(0) {};

constexpr LevelMask_c &LevelMask_c::None() {
    mask_ = 0;
    return *this;
};

LevelMask_c &LevelMask_c::All() {
    for (auto l : enum_range(Level_e::begin, Level_e::end)) {
        Set(l);
    }
    return *this;
}

LevelMask_c &LevelMask_c::AtOrAbove(Level_e l) {
    for (auto l : enum_range(l, Level_e::end)) {
        Set(l);
    }
    return *this;
}

LevelMask_c &LevelMask_c::AtOrBelow(Level_e l) {
    for (auto l : enum_range(Level_e::begin, l)) {
        Set(l);
    }
    return *this;
}

LevelMask_c &LevelMask_c::Clear(Level_e l) {
    mask_ &= ~(0x1 << static_cast<std::underlying_type_t<Level_e>>(l));
    return *this;
}

LevelMask_c &LevelMask_c::Set(Level_e l) {
    mask_ |= (0x1 << static_cast<std::underlying_type_t<Level_e>>(l));
    return *this;
}

LevelMask_c &LevelMask_c::Clear(const std::vector<Level_e> &ls) {
    for (auto l : ls) {
        Clear(l);
    }
    return *this;
}

LevelMask_c &LevelMask_c::Set(const std::vector<Level_e> &ls) {
    for (auto l : ls) {
        Set(l);
    }
    return *this;
}

uint32_t LevelToMask(const Level_e &l) {
    return 0x1 << static_cast<std::underlying_type_t<Level_e>>(l);
}

}  // namespace dave::log

