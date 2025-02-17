#pragma once

#include <string>
#include <vector>

#include "davelog/message.h"
#include "davelog/styles.h"

namespace dave::log {

std::string ToJS(const Message_c &m);
std::string ToPrettyDetails(const Message_c &m);
std::string ToTightDetails(const Message_c &m);
std::string ToPlain(const Message_c &m);

}

