//
//  Dual.hpp
//  Diffintegrator
//
//  Created by Ivan on 6/11/24.
//

#ifndef Dual_hpp
#define Dual_hpp

#include <format>
#include <string>

namespace Math {

struct Dual {
    const double real;
    const double infinitesimal;
    
    Dual(double real, double infinitesimal)
    : real(real), infinitesimal(infinitesimal) {}
    
    Dual(double real)
    : real(real), infinitesimal(0) {}
    
    static Dual variable(double real) {
        return { real, 1 };
    }
    
    friend bool operator==(const Dual& lhs, const Dual& rhs);
    
    friend Dual operator-(const Dual& arg);
    
    friend Dual operator+(const Dual& lhs, const Dual& rhs);
    friend Dual operator-(const Dual& lhs, const Dual& rhs);
    friend Dual operator*(const Dual& lhs, const Dual& rhs);
    friend Dual operator/(const Dual& lhs, const Dual& rhs);
    
    operator std::string() const {
        return std::format("Dual({0}, {1})", real, infinitesimal);
    }
    
};

inline bool operator==(const Dual& lhs, const Dual& rhs) {
    return (lhs.real == rhs.real) && (lhs.infinitesimal == rhs.infinitesimal);
}

Dual operator-(const Dual& arg);

Dual operator+(const Dual& lhs, const Dual& rhs);
Dual operator-(const Dual& lhs, const Dual& rhs);
Dual operator*(const Dual& lhs, const Dual& rhs);
Dual operator/(const Dual& lhs, const Dual& rhs);

} /* namespace Math */

Math::Dual pow(const Math::Dual& base, const Math::Dual& exponent);

Math::Dual sqrt(const Math::Dual& arg);
Math::Dual sin(const Math::Dual& arg);
Math::Dual cos(const Math::Dual& arg);
Math::Dual tan(const Math::Dual& arg);
Math::Dual asin(const Math::Dual& arg);
Math::Dual acos(const Math::Dual& arg);
Math::Dual atan(const Math::Dual& arg);
Math::Dual atan2(const Math::Dual& y, const Math::Dual& x);
Math::Dual sinh(const Math::Dual& arg);
Math::Dual cosh(const Math::Dual& arg);
Math::Dual tanh(const Math::Dual& arg);
Math::Dual asinh(const Math::Dual& arg);
Math::Dual acosh(const Math::Dual& arg);
Math::Dual atanh(const Math::Dual& arg);
Math::Dual log10(const Math::Dual& arg);
Math::Dual log2(const Math::Dual& arg);
Math::Dual log(const Math::Dual& arg);
Math::Dual exp(const Math::Dual& arg);

#endif /* Dual_hpp */
