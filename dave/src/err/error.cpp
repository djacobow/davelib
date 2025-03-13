#include <cstddef>
#include <format>
#include <string>
#include <utility>

#include "dave/inc/err/error.h"
#include "dave/inc/util/enum_helper.h"

namespace dave::err {

EH_IMPL_ENUM_STRINGIFIER(etype_e_to_string, etype_e, DAVE_ERRORS);

Error_c::Error_c(etype_e t, std::string msg, std::string file, std::string func, size_t line) :
    etype_(t),
    message_(std::move(msg)),
    file_(std::move(file)),
    func_(std::move(func)),
    line_(line) {
}

auto Error_c::ok() const -> bool {
    return etype_ == etype_e::ok;
}

auto Error_c::error() const -> etype_e {
    return etype_;
}

auto Error_c::ename() const -> std::string {
    return etype_e_to_string(etype_);
}

auto Error_c::why() const -> std::string {
    if (file_.empty()) {
        return std::format("[etype::{}]: {}", etype_e_to_string(etype_), message_);
    }
    return std::format("[etype::{} @ {}/{}():{}]: {}", etype_e_to_string(etype_), file_, func_, line_, message_);
}

}  // namespace dave::err
