#pragma once

#include <string>

#include "dlog/levels.h"
#include "dlog/dtime.h"

namespace dlog {

class Message_c {
  public:
    dave::time::DTime tstamp;
    Level_e level;
    std::string filename;
    size_t line;
    std::string funcname;
    std::string message;
};

}

