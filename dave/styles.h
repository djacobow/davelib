#pragma once

#include "dave/message.h"

namespace dave::log {

enum class Style_e {
    json,
    pretty,
    tight,
    plain,
    decorated_errors,
};

std::string Style(Style_e style, const Message_c &m);

}

