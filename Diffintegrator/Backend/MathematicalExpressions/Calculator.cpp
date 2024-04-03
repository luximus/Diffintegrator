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

double Calc::Calculator::operator()(const Expr::NumberReference& expr) noexcept(false) {
    throw std::runtime_error("NumberReference not supported");
}

double Calc::Calculator::operator()(const Expr::FunctionReference& expr) noexcept(false) {
    throw std::runtime_error("FunctionReference not supported");
}

double Calc::Calculator::operator()(const Expr::Variable& expr) noexcept(false) {
    throw std::runtime_error("Variable not supported");
}

double Calc::Calculator::operator()(const Expr::PrefixOperator<Expr::negate>& expr) {
    return -boost::apply_visitor(*this, expr.argument);
}

double Calc::Calculator::operator()(const Expr::BinaryOperator<Expr::add>& expr) {
    return boost::apply_visitor(*this, expr.left) + boost::apply_visitor(*this, expr.right);
}

double Calc::Calculator::operator()(const Expr::BinaryOperator<Expr::subtract>& expr) {
    return boost::apply_visitor(*this, expr.left) - boost::apply_visitor(*this, expr.right);
}

double Calc::Calculator::operator()(const Expr::BinaryOperator<Expr::multiply>& expr) {
    return boost::apply_visitor(*this, expr.left) * boost::apply_visitor(*this, expr.right);
}

double Calc::Calculator::operator()(const Expr::BinaryOperator<Expr::divide>& expr) {
    return boost::apply_visitor(*this, expr.left) / boost::apply_visitor(*this, expr.right);
}

double Calc::Calculator::operator()(const Expr::BinaryOperator<Expr::exponentiate>& expr) {
    return pow(boost::apply_visitor(*this, expr.left), boost::apply_visitor(*this, expr.right));
}

double Calc::Calculator::operator()(const Expr::CallOperator& expr) noexcept(false) {
    throw std::runtime_error("Call operator not supported");
}

double Calc::Calculator::operator()(const Expr::SquareRoot& expr) {
    return sqrt(boost::apply_visitor(*this, expr.argument()));
}

double Calc::Calculator::operator()(const Expr::NthRoot& expr) {
    using boost::fusion::at_c;
    return pow(boost::apply_visitor(*this, expr.argument<1>()),
               1.0 / boost::apply_visitor(*this, expr.argument<0>()));
}

double Calc::Calculator::operator()(const Expr::Sine& expr) {
    return sin(boost::apply_visitor(*this, expr.argument()));
}

double Calc::Calculator::operator()(const Expr::Cosine& expr) {
    return cos(boost::apply_visitor(*this, expr.argument()));
}

double Calc::Calculator::operator()(const Expr::Tangent& expr) {
    return tan(boost::apply_visitor(*this, expr.argument()));
}

double Calc::Calculator::operator()(const Expr::InverseSine& expr) {
    return asin(boost::apply_visitor(*this, expr.argument()));
}

double Calc::Calculator::operator()(const Expr::InverseCosine& expr) {
    return acos(boost::apply_visitor(*this, expr.argument()));
}

double Calc::Calculator::operator()(const Expr::InverseTangent& expr) {
    return atan(boost::apply_visitor(*this, expr.argument()));
}

double Calc::Calculator::operator()(const Expr::InverseTangent2& expr) {
    return atan2(boost::apply_visitor(*this, expr.argument<0>()),
                 boost::apply_visitor(*this, expr.argument<1>()));
}

double Calc::Calculator::operator()(const Expr::HyperbolicSine& expr) {
    return sinh(boost::apply_visitor(*this, expr.argument()));
}

double Calc::Calculator::operator()(const Expr::HyperbolicCosine& expr) {
    return cosh(boost::apply_visitor(*this, expr.argument()));
}

double Calc::Calculator::operator()(const Expr::HyperbolicTangent& expr) {
    return tanh(boost::apply_visitor(*this, expr.argument()));
}

double Calc::Calculator::operator()(const Expr::InverseHyperbolicSine& expr) {
    return asinh(boost::apply_visitor(*this, expr.argument()));
}

double Calc::Calculator::operator()(const Expr::InverseHyperbolicCosine& expr) {
    return acosh(boost::apply_visitor(*this, expr.argument()));
}

double Calc::Calculator::operator()(const Expr::InverseHyperbolicTangent& expr) {
    return atanh(boost::apply_visitor(*this, expr.argument()));
}

double Calc::Calculator::operator()(const Expr::Log10& expr) {
    return log10(boost::apply_visitor(*this, expr.argument()));
}

double Calc::Calculator::operator()(const Expr::Log2& expr) {
    return log2(boost::apply_visitor(*this, expr.argument()));
}

double Calc::Calculator::operator()(const Expr::NaturalLog& expr) {
    return log(boost::apply_visitor(*this, expr.argument()));
}

double Calc::Calculator::operator()(const Expr::Logarithm& expr) {
    return log(boost::apply_visitor(*this, expr.argument<1>())) 
           / log(boost::apply_visitor(*this, expr.argument<0>()));
}

double Calc::Calculator::operator()(const Expr::Exp& expr) {
    return exp(boost::apply_visitor(*this, expr.argument()));
}

