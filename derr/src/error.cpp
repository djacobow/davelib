#include <format>

#include "derr/error.h"

namespace derr {

EH_IMPL_ENUM_STRINGIFIER(etype_e_to_string, etype_e, DAVE_ERRORS);

Error::Error(etype_e t, const std::string &msg, const std::string &file, const std::string &func, size_t line) :
    etype_(t),
    message_(msg),
    file_(file),
    func_(func),
    line_(line) {
}

bool Error::ok() const {
    return etype_ == etype_e::ok;
}

etype_e Error::error() const {
    return etype_;
}

const std::string Error::ename() const {
    return etype_e_to_string(etype_);
}

const std::string Error::why() const {
    if (file_.empty()) {
        return std::format("(etype::{}: {}", etype_e_to_string(etype_), message_);
    }
    return std::format("(etype::{} @ {}/{}():{}): {}", etype_e_to_string(etype_), file_, func_, line_, message_);
}

}

