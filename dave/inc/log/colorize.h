#pragma once

#include <string>
#include "dave/inc/log/levels.h"

namespace dave::log {

std::string &Colorize(Level_e l, std::string &os);

}

