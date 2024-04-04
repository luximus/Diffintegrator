//
//  Calculator.hpp
//  Diffintegrator
//
//  Created by Ivan on 4/3/24.
//

#ifndef Calculator_hpp
#define Calculator_hpp

#include <boost/variant/apply_visitor.hpp>
#include <boost/variant/static_visitor.hpp>

#include "Expression.hpp"

namespace Calc {

class Calculator : public boost::static_visitor<double> {
public:
    
    double operator()(const double& value) { return value; }
    
    double operator()(const Expr::NumberReference& expr);
    double operator()(const Expr::FunctionReference& expr);
    double operator()(const Expr::Variable& expr);
    double operator()(const Expr::PrefixOperator<Expr::negate>& expr);
    double operator()(const Expr::BinaryOperator<Expr::add>& expr);
    double operator()(const Expr::BinaryOperator<Expr::subtract>& expr);
    double operator()(const Expr::BinaryOperator<Expr::multiply>& expr);
    double operator()(const Expr::BinaryOperator<Expr::divide>& expr);
    double operator()(const Expr::BinaryOperator<Expr::exponentiate>& expr);
    double operator()(const Expr::CallOperator& expr);
    double operator()(const Expr::SquareRoot& expr);
    double operator()(const Expr::NthRoot& expr);
    double operator()(const Expr::Sine& expr);
    double operator()(const Expr::Cosine& expr);
    double operator()(const Expr::Tangent& expr);
    double operator()(const Expr::InverseSine& expr);
    double operator()(const Expr::InverseCosine& expr);
    double operator()(const Expr::InverseTangent& expr);
    double operator()(const Expr::InverseTangent2& expr);
    double operator()(const Expr::HyperbolicSine& expr);
    double operator()(const Expr::HyperbolicCosine& expr);
    double operator()(const Expr::HyperbolicTangent& expr);
    double operator()(const Expr::InverseHyperbolicSine& expr);
    double operator()(const Expr::InverseHyperbolicCosine& expr);
    double operator()(const Expr::InverseHyperbolicTangent& expr);
    double operator()(const Expr::Log10& expr);
    double operator()(const Expr::Log2& expr);
    double operator()(const Expr::NaturalLog& expr);
    double operator()(const Expr::Logarithm& expr);
    double operator()(const Expr::Exp& expr);
};

} /* namespace Calc */

#endif /* Calculator_hpp */
