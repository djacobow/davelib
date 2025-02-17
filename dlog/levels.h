#pragma once

#include <cstdint>
#include <vector>
#include <string>

#include "dlog/enum_helper.h"
#include "dlog/levels_names.h"

namespace dlog {

EH_DECL_ENUM(Level_e, LOG_LEVELS, vverbose, fatal);
EH_DECL_ENUM_STRINGIFIER(get_Level_e_str, Level_e);

class LevelMask_c {
  public:
    LevelMask_c();
    constexpr LevelMask_c &None();
    LevelMask_c &All();
    LevelMask_c &AtOrAbove(Level_e l);
    LevelMask_c &AtOrBelow(Level_e l);
    LevelMask_c &Clear(Level_e l);
    LevelMask_c &Set(Level_e l);
    LevelMask_c &Clear(const std::vector<Level_e> &ls);
    LevelMask_c &Set(const std::vector<Level_e> &ls);
    uint32_t GetMask() const {
        return mask_;
    }
    bool Contains(Level_e l) const;

  private:
    uint32_t mask_;
};

uint32_t LevelToMask(const Level_e &l);

}  // namespace dlog

