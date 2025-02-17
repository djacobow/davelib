#include <iostream>
#include <string>
#include <unistd.h>
#include <cstdio>

#include "davelog/subscriber.h"
#include "davelog/colors.h"
#include "davelog/formatters.h"
#include "davelog/colorize.h"

namespace dave::log {

static const constexpr std::string newline("\n");

void Subscriber_Base_c::Log(const Message_c &m) {
    auto mask = LevelToMask(m.level);
    if (mask & level_mask_.GetMask()) {
        LogInternal(m);
    }
}

Subscriber_Base_c::Subscriber_Base_c(LevelMask_c lm, Style_e s) :
    style_(s),
    level_mask_(lm) {};

void Subscriber_Base_c::Close() {};

Subscriber_FilePtr_c::Subscriber_FilePtr_c(FILE *of, LevelMask_c lm, Style_e s) :
    Subscriber_Base_c(lm, s),
    ofile_(of) {};

void Subscriber_FilePtr_c::Close() {
    fclose(ofile_);
}

void Subscriber_FilePtr_c::LogInternal(const Message_c &m) {
    auto os = Style(style_, m);

    if ((ofile_ == stdout) && isatty(fileno(ofile_))) {
        Colorize(m.level, os);
    }

    fwrite(os.c_str(), 1, os.size(), ofile_);
    fwrite(newline.c_str(), 1, newline.size(), ofile_);
}

}
