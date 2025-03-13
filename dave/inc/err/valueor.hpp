#pragma once

#include <string>
#include <variant>
#include <stdexcept>

#include "dave/inc/err/error.h"

namespace dave::err {

template<typename T>
class ValueOr_c {
    public:
        ValueOr_c(T &&t) : v_(std::move(t)) {};
        ValueOr_c(Error_c &&e) : v_(std::move(e)) {}
        bool ok() const {
            return std::holds_alternative<T>(v_);
        }
        T &v() {
            return value();
        }
        T &value() {
            if (!std::holds_alternative<T>(v_)) {
                throw std::invalid_argument("no value");
            }
            return std::get<T>(v_);
        }
        Error_c error() const {
            if (!std::holds_alternative<Error_c>(v_)) {
                return Error_c(etype_e::ok, "no error");
            }
            return std::get<Error_c>(v_);
        }
        std::string why() const {
            if (!std::holds_alternative<Error_c>(v_)) {
                return "it's fine!";
            }
            return std::get<Error_c>(v_).why();
        }

    private:
        std::variant<T, Error_c> v_;
};

}

