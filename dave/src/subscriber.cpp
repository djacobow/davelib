#include "dave/subscriber.h"

#include <cstdlib>
#include <iostream>
#include <string>
#include <unistd.h>

#include "dave/colorize.h"
#include "dave/message.h"
#include "dave/styles.h"

namespace dave::log {

static const constexpr std::string newline("\n");

void Subscriber_Base_c::Log(const Message_c &m) {
    if (level_mask_.Contains(m.level)) {
        LogInternal(m);
    }
}

Subscriber_Base_c::Subscriber_Base_c(LevelMask_c lm, Style_e s) :
    style_(s),
    level_mask_(lm) {};

void Subscriber_Base_c::Close() {};

Subscriber_FilePtr_c::Subscriber_FilePtr_c(FILE *of, LevelMask_c lm, Style_e s) :
    Subscriber_Base_c(lm, s),
    ofile_(of),
    colorizable_((of == stdout) && (isatty(fileno(of)) != 0) && (getenv("DLOG_NOCOLOR") == nullptr)) {
}

void Subscriber_FilePtr_c::Close() {
    fclose(ofile_);
}

void Subscriber_FilePtr_c::LogInternal(const Message_c &m) {
    auto os = Style(style_, m);
    if (colorizable_) {
        Colorize(m.level, os);
    }

    fwrite(os.c_str(), 1, os.size(), ofile_);
    fwrite(newline.c_str(), 1, newline.size(), ofile_);
}

}  // namespace dave::log
