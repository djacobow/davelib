#pragma once

#include <string>

namespace dave::log {

// opens console and the file named
void InitLogger(const std::string &fn);
// opens console only
void InitLogger();

}
