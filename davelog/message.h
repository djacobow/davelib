#pragma once

#include <string>

#include "davelog/levels.h"
#include "davelog/dtime.h"

namespace dave::log {

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

