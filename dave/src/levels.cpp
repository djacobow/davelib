#include "dave/levels.h"

#include <vector>

#include "dave/enum_helper.h"
#include "dave/enum_range.h"
#include "dave/levels_names.h"

namespace dave::log {

EH_IMPL_ENUM_STRINGIFIER(get_Level_e_str, Level_e, LOG_LEVELS);


LevelMask_c::LevelMask_c() : mask_(0) {};

constexpr auto LevelMask_c::None() -> LevelMask_c & {
    mask_ = 0;
    return *this;
};

auto LevelMask_c::All() -> LevelMask_c & {
    for (const auto l : enum_range(Level_e::begin, Level_e::end)) {
        Set(l);
    }
    return *this;
}

auto LevelMask_c::AtOrAbove(Level_e l) -> LevelMask_c & {
    for (auto l : enum_range(l, Level_e::end)) {
        Set(l);
    }
    return *this;
}

auto LevelMask_c::AtOrBelow(Level_e l) -> LevelMask_c & {
    for (auto l : enum_range(Level_e::begin, l)) {
        Set(l);
    }
    return *this;
}

auto LevelMask_c::Clear(Level_e l) -> LevelMask_c & {
    mask_ &= ~(0x1 << static_cast<std::underlying_type_t<Level_e>>(l));
    return *this;
}

auto LevelMask_c::Set(Level_e l) -> LevelMask_c & {
    mask_ |= (0x1 << static_cast<std::underlying_type_t<Level_e>>(l));
    return *this;
}

auto LevelMask_c::Clear(const std::vector<Level_e> &ls) -> LevelMask_c & {
    for (auto l : ls) {
        Clear(l);
    }
    return *this;
}

auto LevelMask_c::Set(const std::vector<Level_e> &ls) -> LevelMask_c & {
    for (auto l : ls) {
        Set(l);
    }
    return *this;
}

auto LevelToMask(const Level_e &l) -> uint32_t {
    return 0x1 << static_cast<std::underlying_type_t<Level_e>>(l);
}

auto LevelMask_c::Contains(Level_e l) const -> bool {
  return (LevelToMask(l) & mask_) != 0U;
}

}  // namespace dave::log

