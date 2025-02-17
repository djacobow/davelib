#include <vector>
#include <numeric>
#include "dlog/colors.h"

namespace dlog {

const constexpr std::string code_start = {  0x1b, '[' };
const constexpr std::string code_end   = { 'm' };

constexpr std::string colorModeOn(const ColorTuple_t &ct) { 
    std::vector<std::string> codes;

    if (ct.m_ != ColorMode_e::nochange) {
        codes.push_back(
            std::to_string(static_cast<std::underlying_type_t<ColorMode_e>>(ct.m_))
        );
    }

    if (ct.fg_ != Color_e::nochange) {
        codes.push_back(
            "3" +
            std::to_string(static_cast<std::underlying_type_t<Color_e>>(ct.fg_))
        );
    } 

    if (ct.bg_ != Color_e::nochange) {
        codes.push_back(
            "4" +
            std::to_string(static_cast<std::underlying_type_t<Color_e>>(ct.bg_))
        );
    }

    if (!codes.empty()) {
        auto command = 
            code_start +
            std::accumulate(
               codes.begin(),
               codes.end(),
               std::string(),
               [](std::string ss, std::string s) {
                   return ss.empty() ? s : ss + ';' + s; 
               }
            ) +
            code_end;
        return command;
    }
    return "";
}

constexpr std::string colorReset() {
    return code_start + '0' + code_end;
}

[[maybe_unused]] std::string &colorModeWrap(const ColorTuple_t &ct, std::string &s) {
    s.insert(0, colorModeOn(ct));
    s.append(colorReset());
    return s;
};

}

