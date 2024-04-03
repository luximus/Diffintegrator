//
//  Exceptions.cpp
//  Diffintegrator
//
//  Created by Ivan on 4/3/24.
//

#include "Exceptions.hpp"

#include <stdexcept>

Expr::ArgumentError::ArgumentError(const char *const message)
: std::runtime_error(message) {};

char const* Expr::ArgumentError::what() const noexcept(true) {
    return exception::what();
}

Expr::DomainError::DomainError(const char *const message)
: std::runtime_error(message) {};

char const* Expr::DomainError::what() const noexcept(true) {
    return exception::what();
}
