#pragma once

#include "dlog/message.h"

namespace dlog {

enum class Style_e {
    json,
    pretty,
    tight,
    plain,
    decorated_errors,
};

std::string Style(Style_e style, const Message_c &m);

}

