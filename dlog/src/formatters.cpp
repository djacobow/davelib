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

std::string ToTightDetails(const Message_c &m) {
    std::stringstream os;
    os << m.tstamp.Iso8601() << " | "
       << std::setw(8) << get_Level_e_str(m.level) << " | "
       << m.filename << ":" << m.line << " " << m.funcname << "()" << " | "
       << m.message;
    return os.str();
};

std::string ToPlain(const Message_c &m) {
    return m.message;
};

}
