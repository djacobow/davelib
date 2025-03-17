#include <cstddef>
#include <string>
#include <sstream>
#include <utility>

#include "dave/inc/err/error.h"
#include "dave/inc/util/enum_helper.h"

namespace dave::err {

static EH_IMPL_ENUM_STRINGIFIER(etype_e_to_string, etype_e, DAVE_ERRORS);

Error_c::Error_c(etype_e t, std::string msg, std::string file, std::string func, size_t line) :
    etype_(t),
    message_(std::move(msg)),
    file_(std::move(file)),
    func_(std::move(func)),
    line_(line) {
}

auto Error_c::Ok() const -> bool {
    return etype_ == etype_e::ok;
}

auto Error_c::Error() const -> etype_e {
    return etype_;
}

auto Error_c::Ename() const -> std::string {
    return etype_e_to_string(etype_);
}

auto Error_c::Why() const -> std::string {
    std::stringstream ss;
    if (file_.empty()) {
        ss << "[type: " << etype_e_to_string(etype_) << "]: " << message_;
        return ss.str();
    }
    ss << "[etype::" << etype_e_to_string(etype_) << " @ " << file_ << "/" << func_ << ":" << line_ << "]: " << message_;
    return ss.str();
}

}  // namespace dave::err
