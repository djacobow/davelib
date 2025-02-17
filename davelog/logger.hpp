#pragma once

#include <string>
#include <sstream>
#include <iostream>
#include <map>
#include <cstdarg>

#include "davelog/subscriber.h"
#include "davelog/levels.h"
#include "davelog/styles.h"

namespace dave::log {

class stream_end_c {
  public:
    const Level_e &level;
    const std::string &filename;
    const size_t line;
    const std::string &funcname;
};

class Logger_c {
  public:
    Logger_c(Logger_c const &) = delete;
    void operator=(Logger_c const &) = delete;

    static Logger_c &Get() {
        static Logger_c instance;
        return instance;
    }
    void AddSubscriber(const std::string &name, std::unique_ptr<Subscriber_Base_c> s);

    void Log(const Message_c &m);

    template<Level_e level>
    void Log(
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

    void Log(
        const Level_e &level,
        const std::string &filename,
        const size_t line,
        const std::string &funcname,
        const char *fmt,
        ...
    );
    void Log(
        const Level_e &level,
        const std::string &filename,
        const size_t line,
        const std::string &funcname,
        const char *fmt,
        va_list args
    );

    Logger_c &operator<<(const stream_end_c &x);

    template<class T>
    Logger_c &operator<<(const T &x) {
        ss_ << x;
        return *this;
    }

    void Done();

  private:
    Logger_c() = default;
    std::map<std::string, std::unique_ptr<Subscriber_Base_c> > subscribers_;
    std::ostringstream ss_;
};

}  // namespace dave::log

