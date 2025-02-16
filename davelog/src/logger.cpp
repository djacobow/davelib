#include <string>
#include <vector>
#include <cstdarg>
#include "davelog/logger.hpp"

namespace dave::log {

void Logger_c::Log(
    const Level_e &level,
    const std::string &filename,
    const size_t line,
    const std::string &funcname,
    const char *fmt,
    va_list args) {

    const dave::time::DTime tstamp;

    va_list args_copy;
    va_copy(args_copy, args);

    const int size = vsnprintf(nullptr, 0, fmt, args);
    if (size < 0) {
        va_end(args_copy);
        return;
    }

    std::vector<char> buf(size + 1);
    vsnprintf(buf.data(), buf.size(), fmt, args_copy);
    va_end(args_copy);
    const std::string message(buf.data());

    const Message_c m = {
        .tstamp = tstamp,
        .level = level,
        .filename = filename,
        .line = line,
        .funcname = funcname,
        .message = message
    };

    Log(m);
}

void Logger_c::Log(
    const Level_e &level,
    const std::string &filename,
    const size_t line,
    const std::string &funcname,
    const char *fmt,
    ...
) {

    va_list args;
    va_start(args, fmt);
    Log(level, filename, line, funcname, fmt, args);
    va_end(args);
}

void Logger_c::Log(const Message_c &m) {
    for (auto &it : subscribers_) {
        it.second->Log(m);
    }
}

void Logger_c::Done() {
    for (auto &it : subscribers_) {
        it.second->Close();
    }
    subscribers_.clear();
}

Logger_c &Logger_c::operator<<(const stream_end_c &x) {
    Log(x.level, x.filename, x.line, x.funcname, ss_.str().c_str());
    ss_.str("");
    return *this;
}

void Logger_c::AddSubscriber(
    const std::string &name,
    std::unique_ptr<Subscriber_Base_c> s
) {
    subscribers_[name] = std::move(s);
}

}  // namespace dave::log

