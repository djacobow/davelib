#pragma once

#include <string>

#include "dave/levels.h"
#include "dave/dtime.h"

namespace dave::log {

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

