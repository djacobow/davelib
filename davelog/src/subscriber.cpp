#include <iostream>
#include <string>
#include <nlohmann/json.hpp>

#include "davelog/subscriber.h"

namespace dave::log {

void Subscriber_Base_c::Log(const Message_c &m) {
    auto mask =
        ~(0x1 << static_cast<std::underlying_type_t<decltype(m.level)> >(m.level));
    if (mask & level_mask_.GetMask()) {
        LogInternal(m);
    }
}

Subscriber_Base_c::Subscriber_Base_c(LevelMask_c lm, Style_e s) :
    style_(s),
    level_mask_(lm) {};

void Subscriber_Base_c::Close() {};

// NOLINTNEXTLINE(readability-convert-member-functions-to-static)
std::string Subscriber_Base_c::ToJS(const Message_c &m) const {
    const nlohmann::json j = {
        {"time", m.tstamp.Iso8601()},
        {"level", get_Level_e_str(m.level)},
        {"file", m.filename},
        {"line", std::to_string(m.line)},
        {"function", m.funcname},
        {"message", m.message},
    };
    return j.dump() + "\n";
};

// NOLINTNEXTLINE(readability-convert-member-functions-to-static)
std::string Subscriber_Base_c::ToPrettyDetails(const Message_c &m) const {
    std::stringstream os;
    os << m.tstamp.Iso8601() << " | " << std::setw(10) << std::setfill(' ')
       << get_Level_e_str(m.level) << " | ";
    std::stringstream fs;
    fs << m.filename << ":" << m.line << " " << m.funcname << "()";
    os << std::setw(35) << fs.str() << "\n";
    os << "    " << std::setw(0) << m.message << "\n";
    return os.str();
};

// NOLINTNEXTLINE(readability-convert-member-functions-to-static)
std::string Subscriber_Base_c::ToTightDetails(const Message_c &m) const {
    std::stringstream os;
    os << m.tstamp.Iso8601() << " | "
       << get_Level_e_str(m.level) << " | "
       << m.filename << ":" << m.line << " " << m.funcname << "()" << " | "
       << m.message << "\n";
    return os.str();
};

// NOLINTNEXTLINE(readability-convert-member-functions-to-static)
std::string Subscriber_Base_c::ToPlain(const Message_c &m) const {
    return m.message + "\n";
};

Subscriber_FilePtr_c::Subscriber_FilePtr_c(FILE *of, LevelMask_c lm, Style_e s) :
    Subscriber_Base_c(lm, s),
    ofile_(of) {};

void Subscriber_FilePtr_c::Close() {
    fclose(ofile_);
}

void Subscriber_FilePtr_c::LogInternal(const Message_c &m) {
    std::string os;
    switch (style_) {
        case Style_e::pretty:
            os = ToPrettyDetails(m);
            break;
        case Style_e::tight:
            os = ToTightDetails(m);
            break;
        case Style_e::json:
            os = ToJS(m);
            break;
        case Style_e::plain:
            os = ToPlain(m);
            break;
        case Style_e::decorated_errors:
            if (m.level >= Level_e::warning) {
                os = ToTightDetails(m);
            } else {
                os = ToPlain(m);
            }
            break;
        default:
            break;
    }
    fwrite(os.c_str(), 1, strlen(os.c_str()), ofile_);
}

}
