#pragma once

#include <string>

#include "dlog/enum_helper.h"

namespace derr {

#define DAVE_ERRORS(X)  \
    X(ok) \
    X(cancelled) \
    X(invalid_argument) \
    X(timeout) \
    X(notfound) \
    X(alreadyexists) \
    X(permission) \
    X(authentication) \
    X(resource) \
    X(precondition) \
    X(aborted) \
    X(unavailable) \
    X(range) \
    X(unimplemented) \
    X(internal) \
    X(loss) \
    X(unknown) \

EH_DECL_ENUM(errors_e, DAVE_ERRORS, ok, unknown);

EH_DECL_ENUM_STRINGIFIER(errors_s_to_string, errors_e);

class Error {
    public:
        Error(errors_e t, std::string &&m = "");
        bool ok() const;
        const std::string why() const;
        const std::string ename() const;
        errors_e error() const;

    private:
        errors_e etype_;
        std::string message_;
};

}

