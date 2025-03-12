#include "dave/logger.hpp"

#include <cstdarg>
#include <cstddef>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "dave/dtime.h"
#include "dave/levels.h"
#include "dave/message.h"

namespace dave::log {

void Logger_c::Log(
    const Level_e &level,
    const std::string &filename,
    const size_t line,
    const std::string &funcname,
    const std::string &fmt,
    va_list args) {

    const dave::time::DTime tstamp;

    va_list copy_1;
    va_copy(copy_1, args);
    // TODO(user): clang-tidy complains:
    //   logger.cpp:21:22: warning: Function 'vsnprintf' is called with an uninitialized
    //   va_list argument [clang-analyzer-valist.Uninitialized]
    // We need to figure out how to fix this, since the copy is supposed to be "started"
    // automatically. The second call below, which writes that actual string does
    // not complain, even though the copy is made in the same manner.
    const int size = vsnprintf(nullptr, 0, fmt.c_str(), copy_1); // NOLINT
    va_end(copy_1);
    if (size < 0) {
        return;
    }

    std::vector<char> buf(size + 1);
    va_list copy_2;
    va_copy(copy_2, args);
    vsnprintf(buf.data(), buf.size(), fmt.c_str(), copy_2);
    va_end(copy_2);
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
    const std::string fmt,
    ...
) {

    va_list args;
    va_start(args, fmt);
    Log(level, filename, line, funcname, fmt, args);
    va_end(args);
}

void Logger_c::Log(const Message_c &m) {
    for (auto &it : subscribers_) {
        const std::lock_guard<std::mutex> lock(mtx_);
        it.second->Log(m);
    }
}

void Logger_c::Done() {
    for (auto &it : subscribers_) {
        it.second->Close();
    }
    subscribers_.clear();
}

auto Logger_c::operator<<(const stream_end_c &x) -> Logger_c & {
    Log(x.level, x.filename, x.line, x.funcname, ss_.str());
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

