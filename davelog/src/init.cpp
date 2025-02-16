#include <string>
#include "davelog/init.h"
#include "davelog/logger.hpp"

namespace dave::log {

void InitLogger() {
    Logger_c::Get().AddSubscriber(
        "console",
        std::make_unique<Subscriber_FilePtr_c>(
            stdout,
            LevelMask_c().AtOrAbove(Level_e::info),
            Style_e::decorated_errors
        )
    );
}

void InitLogger(const std::string &fn) {
    InitLogger();
    FILE *lfh = fopen(fn.c_str(), "a");
    Logger_c::Get().AddSubscriber(
        "logfile",
        std::make_unique<Subscriber_FilePtr_c>(lfh, LevelMask_c().All(), Style_e::json)
    );
};

}  // namespace dave::log

