#include <iostream>
#include <sstream>
#include <string>
#include <nlohmann/json.hpp>

#include "dlog/formatters.h"

namespace dlog {

std::string ToJS(const Message_c &m) {
    const nlohmann::json j = {
        {"time", m.tstamp.Iso8601()},
        {"level", get_Level_e_str(m.level)},
        {"file", m.filename},
        {"line", std::to_string(m.line)},
        {"function", m.funcname},
        {"message", m.message},
    };
    return j.dump();
};

std::string ToPrettyDetails(const Message_c &m) {
    std::stringstream os;
    os << m.tstamp.Iso8601() << " | " << std::setw(8) << std::setfill(' ')
       << get_Level_e_str(m.level) << " | ";
    std::stringstream fs;
    fs << m.filename << ":" << m.line << " " << m.funcname << "()";
    os << std::setw(35) << fs.str() << "\n";
    os << "    " << std::setw(0) << m.message;
    return os.str();
};

// print a thing or the thing's length in spaces, depending
static std::string maybeSkip(bool skip, const std::string &s) {
    return skip ? std::string(s.size(), ' ') : s;
}

std::string ToTightDetails(const Message_c &m) {
    static Message_c last_m = { .tstamp = dave::time::DTime(0) };
    std::stringstream os;
    os << maybeSkip(last_m.tstamp.SameMillis(m.tstamp), m.tstamp.Iso8601()) << " | "
       << std::setw(8)
       << maybeSkip(m.level    == last_m.level,    get_Level_e_str(m.level)) << " | "
       << maybeSkip(m.filename == last_m.filename ,m.filename) << ":"
       << maybeSkip(m.line     == last_m.line,     std::to_string(m.line)) << " "
       << maybeSkip(m.funcname == last_m.funcname, m.funcname + "()") << " | "
       << m.message;
    last_m = std::move(m);
    return os.str();
};

std::string ToPlain(const Message_c &m) {
    return m.message;
};

}
