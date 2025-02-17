#pragma once

#include <string>
#include <vector>

#include "dlog/message.h"
#include "dlog/styles.h"

namespace dlog {

std::string ToJS(const Message_c &m);
std::string ToPrettyDetails(const Message_c &m);
std::string ToTightDetails(const Message_c &m);
std::string ToPlain(const Message_c &m);

}

