#include "dave/styles.h"
#include <string>

#include "dave/formatters.h"
#include "dave/levels.h"
#include "dave/message.h"

namespace dave::log {

auto Style(Style_e s, const Message_c &m) -> std::string {
    std::string os;
    switch (s) {
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
    return os;
};

}  // namespace dave::log
