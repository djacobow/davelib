#pragma once

#include <string>
#include <sstream>
#include <map>
#include <memory>
#include <cstdarg>
#include <mutex>

#include "dave/inc/log/subscriber.h"
#include "dave/inc/log/levels.h"

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

    void Log(
        const Level_e &level,
        const std::string &filename,
        size_t line,
        const std::string &funcname,
        // Not this is purposefully not a ref to avoid UB associated
        // with starting varargs from a reference:
         std::string fmt,
        ...
    );
    void Log(
        const Level_e &level,
        const std::string &filename,
        size_t line,
        const std::string &funcname,
        const std::string &fmt,
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
    std::mutex mtx_;
};

} // namespace dave::log

