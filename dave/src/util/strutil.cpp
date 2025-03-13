#include "dave/inc/util/strutil.h"
#include <iostream>
#include <iomanip>
#include <iterator>
#include <numeric>
#include <cstdint>
#include <sstream>
#include <string_view>

namespace dave::str {

const constexpr std::string newline("\n");

auto split(const std::string &s, const std::string &delim) -> std::vector<std::string> {
    size_t pos_start = 0;
    const size_t delim_len = delim.length();
    size_t pos_end;
    std::string tok;
    std::vector<std::string> res;
    while ((pos_end = s.find_first_of(delim, pos_start)) != std::string::npos) {
        tok = s.substr(pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.emplace_back(tok);
    }
    res.push_back(s.substr(pos_start));
    return res;
}

auto stringOrSpace(bool skip, const std::string &s) -> std::string {
    return skip ? std::string(s.size(), ' ') : s;
}

auto join(const std::vector<std::string> &joinees, const std::string &joiner) -> std::string {
    if (joinees.empty()) {
        return "";
    }

    return std::accumulate(
        std::begin(joinees),
        std::end(joinees),
        std::string(),
        [&joiner](std::string ss, const std::string &s) {
            return ss.empty() ? s : ss + joiner + s;
        }
    );
}

auto repeat(const std::string &s, uint32_t n) -> std::string {
    std::string os;
    for (uint32_t i=0; i<n; i++) {
        os += s;
    }
    return os;
}

auto split_white(const std::string &s) -> std::vector<std::string> {
    std::istringstream bs(s);
    std::vector<std::string> ret{
        std::istream_iterator<std::string>(bs), 
        std::istream_iterator<std::string>()
    };
    return ret;
}

auto wrap(const std::string &s, uint32_t max_w) -> std::vector<std::string> {
    std::vector<std::string> ov;
    auto words = split_white(s);
    std::vector<std::string> olv;
    uint32_t olv_size = 0;
    for (const auto &w : words) {
        if (((olv_size + w.size() + 1) > max_w)) {
            ov.push_back(join(olv, " "));
            olv.clear();
            olv_size = 0;
        }
        olv.push_back(w);
        olv_size += w.size() + 1;
    }
    if (!olv.empty()) {
        ov.push_back(join(olv, " "));
    }
    return ov;
}

namespace draw {
    const constexpr std::string ul("\u256d");
    const constexpr std::string ur("\u256e");
    const constexpr std::string lr("\u256f");
    const constexpr std::string ll("\u2570");
    const constexpr std::string h("\u2500");
    const constexpr std::string v("\u2502");
    const constexpr std::string to("\u2524");
    const constexpr std::string tc("\u251c");
    const constexpr std::string ovflw("+>");
} // namespace draw

auto box(const std::string &title, const std::vector<std::string> &lines, uint32_t width) -> std::string {
    const uint32_t TITLE_OVERHEAD = 5;
    const uint32_t title_len = TITLE_OVERHEAD + title.size();
    if (title_len >= width) {
        width = title_len + 1;
    }
    const uint32_t top_h_count = width - title_len;
    std::stringstream ss;
    if (!title.empty()) {
        ss << draw::ul << draw::h << draw::to << " " << title
           << " " << draw::tc << repeat(draw::h, top_h_count)
           << draw::ur << newline;
    } else {
        ss << draw::ul << repeat(draw::h, width) << draw::ur
           << newline;
    }
    for (const auto &l : lines) {
        const uint32_t csize = l.size();
        if (csize <= width) {
            ss << draw::v << std::left << std::setw(static_cast<int>(width)) << l
               << std::setw(0);
        } else {
            ss << draw::v << l.substr(0,width-draw::ovflw.size()) << draw::ovflw << std::setw(0);
        }
        ss << draw::v << newline;
    }
    ss << draw::ll << repeat(draw::h, width) << draw::lr << newline;
    return ss.str(); 
}


} // namespace dave::str
