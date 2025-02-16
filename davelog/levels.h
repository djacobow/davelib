#pragma once

#include <cstdint>
#include <vector>

#include "davelog/enum_helper.h"

#define LOG_LEVELS(X) \
    X(very_verbose) \
    X(verbose) \
    X(debug) \
    X(info) \
    X(notice) \
    X(warning) \
    X(error) \
    X(fatal)

namespace dave::log {

EH_DECL_ENUM(Level_e, LOG_LEVELS, very_verbose, fatal);
EH_DECL_ENUM_STRINGIFIER(get_Level_e_str, Level_e);

class LevelMask_c {
  public:
    LevelMask_c();
    constexpr LevelMask_c &None();
    //constexpr LevelMask_c &all();
    LevelMask_c &All();
    LevelMask_c &AtOrAbove(Level_e l);
    LevelMask_c &Clear(Level_e l);
    LevelMask_c &Set(Level_e l);
    LevelMask_c &Clear(const std::vector<Level_e> &ls);
    LevelMask_c &Set(const std::vector<Level_e> &ls);
    uint32_t GetMask() const {
        return mask_;
    }

  private:
    uint32_t mask_;
};
}
