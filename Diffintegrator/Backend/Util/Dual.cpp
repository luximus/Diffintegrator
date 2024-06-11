//
//  Dual.cpp
//  Diffintegrator
//
//  Created by Ivan on 6/11/24.
//

#include "Dual.hpp"

Math::Dual Math::operator-(const Math::Dual& arg) {
    return { -arg.real, -arg.infinitesimal };
}

Math::Dual Math::operator+(const Math::Dual& lhs, const Math::Dual& rhs) {
    return { lhs.real + rhs.real, lhs.infinitesimal + rhs.infinitesimal };
}

Math::Dual Math::operator-(const Math::Dual& lhs, const Math::Dual& rhs) {
    return { lhs.real - rhs.real, lhs.infinitesimal - rhs.infinitesimal };
}

Math::Dual Math::operator*(const Math::Dual& lhs, const Math::Dual& rhs) {
    return { lhs.real * rhs.real, lhs.real * rhs.infinitesimal + lhs.infinitesimal * rhs.real };
}

Math::Dual Math::operator/(const Math::Dual& lhs, const Math::Dual& rhs) {
    return { lhs.real / rhs.real, (lhs.infinitesimal * rhs.real - rhs.infinitesimal * lhs.real) / (rhs.real * rhs.real) };
}

Math::Dual pow(const Math::Dual& base, const Math::Dual& exponent) {
    if (base.real == 0) {
        if (exponent.real == 0) {
            return { 1, nan("") };
        }
        return { 0, 0 };
    }
    return { pow(base.real, exponent.real),
             pow(base.real, exponent.real) * (exponent.infinitesimal * log(base.real) + (base.infinitesimal * exponent.real) / base.real) };
}

Math::Dual sqrt(const Math::Dual& arg) {
    return { sqrt(arg.real), arg.infinitesimal / (2 * sqrt(arg.real)) };
}

Math::Dual sin(const Math::Dual& arg) {
    return { sin(arg.real), cos(arg.real) * arg.infinitesimal };
}

Math::Dual cos(const Math::Dual& arg) {
    return { cos(arg.real), -sin(arg.real) * arg.infinitesimal };
}

Math::Dual tan(const Math::Dual& arg) {
    return { tan(arg.real), arg.infinitesimal / (cos(arg.real) * cos(arg.real)) };
}

Math::Dual asin(const Math::Dual& arg) {
    return { asin(arg.real), arg.infinitesimal / sqrt(1 - arg.real * arg.real) };
}

Math::Dual acos(const Math::Dual& arg) {
    return { acos(arg.real), -arg.infinitesimal / sqrt(1 - arg.real * arg.real) };
}

Math::Dual atan(const Math::Dual& arg) {
    return { atan(arg.real), arg.infinitesimal / (1 + arg.real * arg.real) };
}

Math::Dual atan2(const Math::Dual& y, const Math::Dual& x) {
    return { atan2(y.real, x.real),
             (x.real * y.infinitesimal - y.real * x.infinitesimal) / (x.real * x.real + y.real * y.real) };
}

Math::Dual sinh(const Math::Dual& arg) {
    return { sinh(arg.real), cosh(arg.infinitesimal) };
}

Math::Dual cosh(const Math::Dual& arg) {
    return { cosh(arg.real), sinh(arg.infinitesimal) };
}

Math::Dual tanh(const Math::Dual& arg) {
    return { tanh(arg.real), arg.infinitesimal / (cosh(arg.real) * cosh(arg.real)) };
}

Math::Dual asinh(const Math::Dual& arg) {
    return { sinh(arg.real), arg.infinitesimal / sqrt(arg.real * arg.real + 1) };
}

Math::Dual acosh(const Math::Dual& arg) {
    return { cosh(arg.real), arg.infinitesimal / sqrt(arg.real * arg.real - 1) };
}

Math::Dual atanh(const Math::Dual& arg) {
    return { tanh(arg.real), arg.infinitesimal / (1 - arg.real * arg.real) };
}

Math::Dual log10(const Math::Dual& arg) {
    return { log10(arg.real), arg.infinitesimal / (arg.real * log(10)) };
}

Math::Dual log2(const Math::Dual& arg) {
    return { log2(arg.real), arg.infinitesimal / (arg.real * log(2)) };
}

Math::Dual log(const Math::Dual& arg) {
    return { log(arg.real), arg.infinitesimal / arg.real };
}

Math::Dual exp(const Math::Dual& arg) {
    return { exp(arg.real), arg.infinitesimal * exp(arg.real) };
}
