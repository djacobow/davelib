#pragma once

#include <string>
#include <variant>
#include <stdexcept>

#include "derr/error.h"

namespace derr {

template<typename T>
class ValueOr {
    public:
        ValueOr(T &&t) : v_(std::move(t)) {};
        ValueOr(Error &&e) : v_(std::move(e)) {}
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
        Error error() const {
            if (!std::holds_alternative<Error>(v_)) {
                return Error(etype_e::ok, "no error");
            }
            return std::get<Error>(v_);
        }
        std::string why() const {
            if (!std::holds_alternative<Error>(v_)) {
                return "it's fine!";
            }
            return std::get<Error>(v_).why();
        }

    private:
        std::variant<T, Error> v_;
};

}

