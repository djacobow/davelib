#pragma once

#include <string>

#include "dlog/levels.h"
#include "dlog/dtime.h"

namespace dlog {

class Message_c {
  public:
    const dave::time::DTime tstamp;
    const Level_e level;
    const std::string filename;
    const size_t line;
    const std::string funcname;
    std::string message;
};

}

