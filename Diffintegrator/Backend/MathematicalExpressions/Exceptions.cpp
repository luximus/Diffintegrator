//
//  Exceptions.cpp
//  Diffintegrator
//
//  Created by Ivan on 4/3/24.
//

#include "Exceptions.hpp"

#include <stdexcept>

Math::ArgumentError::ArgumentError(const char *const message)
: std::runtime_error(message) {};

char const* Math::ArgumentError::what() const noexcept(true) {
    return exception::what();
}

Math::DomainError::DomainError(const char *const message)
: std::runtime_error(message) {};

char const* Math::DomainError::what() const noexcept(true) {
    return exception::what();
}

Math::ReferenceError::ReferenceError(const char *const message)
: std::runtime_error(message) {};

char const* Math::ReferenceError::what() const noexcept(true) {
    return exception::what();
}
