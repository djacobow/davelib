#include "derr/error.h"

namespace derr {

EH_IMPL_ENUM_STRINGIFIER(errors_e_to_string, errors_e, DAVE_ERRORS);

Error::Error(errors_e t, std::string &&m) : etype_(t), message_(std::move(m)) { }

bool Error::ok() const {
    return etype_ == errors_e::ok;
}

errors_e Error::error() const {
    return etype_;
}

const std::string Error::ename() const {
    return errors_e_to_string(etype_);
}

const std::string Error::why() const {
    return "(errors_e::" + errors_e_to_string(etype_) + ") " + message_;
}

}

