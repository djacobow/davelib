#pragma once

#include <string>

#include "dave/inc/util/enum_helper.h"

namespace dave::err {

#define DAVE_ERRORS(X)  \
    X(ok) \
    X(cancelled) \
    X(invalid_arg) \
    X(timeout) \
    X(not_found) \
    X(exists) \
    X(no_perms) \
    X(no_auth) \
    X(oom) \
    X(oo_something) \
    X(unmet_condition) \
    X(aborted) \
    X(unavailable) \
    X(range) \
    X(unimplemented) \
    X(internal) \
    X(data_loss) \
    X(unknown) \

EH_DECL_ENUM(etype_e, DAVE_ERRORS, ok, unknown);

EH_DECL_ENUM_STRINGIFIER(errors_s_to_string, etype_e);

class Error_c {
    public:
        Error_c(etype_e t,
            std::string msg = "",
            std::string file = "",
            std::string func = "",
            const size_t line = 0
        );
        bool ok() const;
        std::string why() const;
        std::string ename() const;
        etype_e error() const;

    private:
        etype_e etype_;
        std::string message_;
        std::string file_;
        std::string func_;
        size_t line_;
};

}


// short macro that will create an error from scratch, with minimal fuss and with the location info
#define E_(type, msg) dave::err::Error_c(dave::err::etype_e::type, msg, __FILE__, __func__, __LINE__)

