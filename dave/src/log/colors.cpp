#include <numeric>
#include <string>
#include <type_traits>
#include <vector>

#include "dave/inc/log/colors.h"

namespace dave::log {

const constexpr std::string code_start = {  0x1b, '[' };
const constexpr std::string code_end   = { 'm' };

constexpr auto colorModeOn(const ColorTuple_t &ct) -> std::string { 
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
               [](const std::string& ss, const std::string& s) {
                   return ss.empty() ? s : ss + ';' + s; 
               }
            ) +
            code_end;
        return command;
    }
    return "";
}

constexpr auto colorReset() -> std::string {
    return code_start + '0' + code_end;
}

[[maybe_unused]] auto colorModeWrap(const ColorTuple_t &ct, std::string &s) -> std::string & {
    s.insert(0, colorModeOn(ct));
    s.append(colorReset());
    return s;
};

}  // namespace dave::log
