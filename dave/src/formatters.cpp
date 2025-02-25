#include "dave/formatters.h"

#include <iomanip>
#include <nlohmann/json.hpp>
#include <sstream>
#include <string>
#include <vector>

#include "dave/levels.h"
#include "dave/message.h"
#include "dave/strutil.h"

namespace dave::log {

const uint32_t LEVEL_NAME_WIDTH = 8;
const uint32_t FUNC_NAME_WIDTH  = 35;

auto ToJS(const Message_c &m) -> std::string {
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

auto ToPrettyDetails(const Message_c &m) -> std::string {
    std::stringstream os;
    os << m.tstamp.Iso8601() << " | " << std::setw(LEVEL_NAME_WIDTH) << std::setfill(' ')
       << get_Level_e_str(m.level) << " | ";
    std::stringstream fs;
    fs << m.filename << ":" << m.line << " " << m.funcname << "()";
    os << std::setw(FUNC_NAME_WIDTH) << fs.str() << dave::str::newline;
    os << "    " << std::setw(0) << m.message;
    return os.str();
};


auto ToTightDetails(const Message_c &m) -> std::string {
    static Message_c last_m = { .tstamp = dave::time::DTime(0) };
    std::stringstream os;
    const auto lines = dave::str::split(m.message, dave::str::newline);
    const uint32_t num_lines = lines.size();
    for (uint32_t i=0; i<num_lines; i++) {
        os << dave::str::stringOrSpace(last_m.tstamp.SameMillis(m.tstamp), m.tstamp.Iso8601()) << " | "
           << std::setw(LEVEL_NAME_WIDTH)
           << dave::str::stringOrSpace(m.level    == last_m.level,    get_Level_e_str(m.level)) << " | "
           << dave::str::stringOrSpace(m.filename == last_m.filename ,m.filename) << ":"
           << dave::str::stringOrSpace(m.line     == last_m.line,     std::to_string(m.line)) << " "
           << dave::str::stringOrSpace(m.funcname == last_m.funcname, m.funcname + "()") << " | "
           << lines[i];
        if (i < (num_lines-1)) {
           os << dave::str::newline;
        }
        last_m = m;
    }
    return os.str();
};

auto ToPlain(const Message_c &m) -> std::string {
    return m.message;
};

}  // namespace dave::log
