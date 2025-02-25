#include <cstddef>
#include <format>
#include <string>
#include <utility>

#include "dave/error.h"
#include "dave/enum_helper.h"

namespace dave::err {

EH_IMPL_ENUM_STRINGIFIER(etype_e_to_string, etype_e, DAVE_ERRORS);

Error::Error(etype_e t, std::string msg, std::string file, std::string func, size_t line) :
    etype_(t),
    message_(std::move(msg)),
    file_(std::move(file)),
    func_(std::move(func)),
    line_(line) {
}

auto Error::ok() const -> bool {
    return etype_ == etype_e::ok;
}

auto Error::error() const -> etype_e {
    return etype_;
}

auto Error::ename() const -> std::string {
    return etype_e_to_string(etype_);
}

auto Error::why() const -> std::string {
    if (file_.empty()) {
        return std::format("[etype::{}]: {}", etype_e_to_string(etype_), message_);
    }
    return std::format("[etype::{} @ {}/{}():{}]: {}", etype_e_to_string(etype_), file_, func_, line_, message_);
}

}  // namespace dave::err
