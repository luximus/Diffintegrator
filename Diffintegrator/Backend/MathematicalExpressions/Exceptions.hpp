//
//  Exceptions.hpp
//  Diffintegrator
//
//  Created by Ivan on 4/3/24.
//

#ifndef Exceptions_hpp
#define Exceptions_hpp

#include <stdexcept>

namespace Expr {

/**
 Exceptions related to the arguments passed into a function.
 */
class ArgumentError : public std::runtime_error {
public:
    ArgumentError(char const* const message);
    
    virtual char const* what() const noexcept(true);
};

class DomainError : public std::runtime_error {
public:
    DomainError(char const* const message);
    
    virtual char const* what() const noexcept(true);
};

} /* namespace Expr */

#endif /* Exceptions_hpp */
