#pragma once

#include <string>
#include "davelog/levels.h"

namespace dave::log {

std::string &Colorize(Level_e l, std::string &os);

}

