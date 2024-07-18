//
//  Exceptions.hpp
//  Diffintegrator
//
//  Created by Ivan on 4/3/24.
//

#ifndef Exceptions_hpp
#define Exceptions_hpp

#include <stdexcept>

// TODO: Allow these errors to accept error location information

namespace Math {

/**
 An argument was invalid, there are arguments missing, or there are too many arguments.
 */
class ArgumentError : public std::runtime_error {
public:
    ArgumentError(char const* const message);
    
    virtual char const* what() const noexcept(true);
};

/**
 The argument to a mathematical function is outside its domain.
 */
class DomainError : public std::runtime_error {
public:
    DomainError(char const* const message);
    
    virtual char const* what() const noexcept(true);
};

/**
 The value makes no sense because it is of the incorrect type.
 */
class TypeError : public std::runtime_error {
public:
    TypeError(char const* const message);
    
    virtual char const* what() const noexcept(true);
};

/**
 The reference to another number or function could not be resolved.
 */
class ReferenceError : public std::runtime_error {
public:
    ReferenceError(char const* const message);
    
    virtual char const* what() const noexcept(true);
};

} /* namespace Expr */

#endif /* Exceptions_hpp */
