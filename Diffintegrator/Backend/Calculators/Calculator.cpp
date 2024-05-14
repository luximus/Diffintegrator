//
//  Calculator.cpp
//  Diffintegrator
//
//  Created by Ivan on 4/3/24.
//

#include "Calculator.hpp"

#include <exception>

#include <boost/variant/apply_visitor.hpp>
#include <boost/fusion/include/at_c.hpp>

#include "Expression.hpp"

double Math::Calculator::operator()(const Math::NumberReference& expr) noexcept(false) {
    throw std::runtime_error("NumberReference not supported");
}

double Math::Calculator::operator()(const Math::FunctionReference& expr) noexcept(false) {
    throw std::runtime_error("FunctionReference not supported");
}

double Math::Calculator::operator()(const Math::Variable& expr) noexcept(false) {
    throw std::runtime_error("Variable not supported");
}

double Math::Calculator::operator()(const Math::PrefixOperator<Math::negate>& expr) {
    return -boost::apply_visitor(*this, expr.argument);
}

double Math::Calculator::operator()(const Math::BinaryOperator<Math::add>& expr) {
    return boost::apply_visitor(*this, expr.left) + boost::apply_visitor(*this, expr.right);
}

double Math::Calculator::operator()(const Math::BinaryOperator<Math::subtract>& expr) {
    return boost::apply_visitor(*this, expr.left) - boost::apply_visitor(*this, expr.right);
}

double Math::Calculator::operator()(const Math::BinaryOperator<Math::multiply>& expr) {
    return boost::apply_visitor(*this, expr.left) * boost::apply_visitor(*this, expr.right);
}

double Math::Calculator::operator()(const Math::BinaryOperator<Math::divide>& expr) {
    return boost::apply_visitor(*this, expr.left) / boost::apply_visitor(*this, expr.right);
}

double Math::Calculator::operator()(const Math::BinaryOperator<Math::exponentiate>& expr) {
    return pow(boost::apply_visitor(*this, expr.left), boost::apply_visitor(*this, expr.right));
}

double Math::Calculator::operator()(const Math::CallOperator& expr) noexcept(false) {
    throw std::runtime_error("Call operator not supported");
}

double Math::Calculator::operator()(const Math::SquareRoot& expr) {
    return sqrt(boost::apply_visitor(*this, expr.argument()));
}

double Math::Calculator::operator()(const Math::NthRoot& expr) {
    using boost::fusion::at_c;
    return pow(boost::apply_visitor(*this, expr.argument<1>()),
               1.0 / boost::apply_visitor(*this, expr.argument<0>()));
}

double Math::Calculator::operator()(const Math::Sine& expr) {
    return sin(boost::apply_visitor(*this, expr.argument()));
}

double Math::Calculator::operator()(const Math::Cosine& expr) {
    return cos(boost::apply_visitor(*this, expr.argument()));
}

double Math::Calculator::operator()(const Math::Tangent& expr) {
    return tan(boost::apply_visitor(*this, expr.argument()));
}

double Math::Calculator::operator()(const Math::InverseSine& expr) {
    return asin(boost::apply_visitor(*this, expr.argument()));
}

double Math::Calculator::operator()(const Math::InverseCosine& expr) {
    return acos(boost::apply_visitor(*this, expr.argument()));
}

double Math::Calculator::operator()(const Math::InverseTangent& expr) {
    return atan(boost::apply_visitor(*this, expr.argument()));
}

double Math::Calculator::operator()(const Math::InverseTangent2& expr) {
    return atan2(boost::apply_visitor(*this, expr.argument<0>()),
                 boost::apply_visitor(*this, expr.argument<1>()));
}

double Math::Calculator::operator()(const Math::HyperbolicSine& expr) {
    return sinh(boost::apply_visitor(*this, expr.argument()));
}

double Math::Calculator::operator()(const Math::HyperbolicCosine& expr) {
    return cosh(boost::apply_visitor(*this, expr.argument()));
}

double Math::Calculator::operator()(const Math::HyperbolicTangent& expr) {
    return tanh(boost::apply_visitor(*this, expr.argument()));
}

double Math::Calculator::operator()(const Math::InverseHyperbolicSine& expr) {
    return asinh(boost::apply_visitor(*this, expr.argument()));
}

double Math::Calculator::operator()(const Math::InverseHyperbolicCosine& expr) {
    return acosh(boost::apply_visitor(*this, expr.argument()));
}

double Math::Calculator::operator()(const Math::InverseHyperbolicTangent& expr) {
    return atanh(boost::apply_visitor(*this, expr.argument()));
}

double Math::Calculator::operator()(const Math::Log10& expr) {
    return log10(boost::apply_visitor(*this, expr.argument()));
}

double Math::Calculator::operator()(const Math::Log2& expr) {
    return log2(boost::apply_visitor(*this, expr.argument()));
}

double Math::Calculator::operator()(const Math::NaturalLog& expr) {
    return log(boost::apply_visitor(*this, expr.argument()));
}

double Math::Calculator::operator()(const Math::Logarithm& expr) {
    return log(boost::apply_visitor(*this, expr.argument<1>())) 
           / log(boost::apply_visitor(*this, expr.argument<0>()));
}

double Math::Calculator::operator()(const Math::Exp& expr) {
    return exp(boost::apply_visitor(*this, expr.argument()));
}

