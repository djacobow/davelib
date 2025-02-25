#pragma once

#include <string>
#include <vector>

#include "dave/message.h"
#include "dave/styles.h"

namespace dave::log {

std::string ToJS(const Message_c &m);
std::string ToPrettyDetails(const Message_c &m);
std::string ToTightDetails(const Message_c &m);
std::string ToPlain(const Message_c &m);

}

