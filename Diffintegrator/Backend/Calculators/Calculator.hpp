//
//  Calculator.hpp
//  Diffintegrator
//
//  Created by Ivan on 4/3/24.
//

#ifndef Calculator_hpp
#define Calculator_hpp

#include <map>
#include <string>

#include <boost/variant/static_visitor.hpp>

#include "Expression.hpp"
#include "Declaration.hpp"

namespace Math {

class Calculator : public boost::static_visitor<double> {
public:
    
    double operator()(const double& value) { return value; }
    
    double operator()(const Math::NumberReference& expr);
    double operator()(const Math::FunctionReference& expr);
    double operator()(const Math::Variable& expr);
    double operator()(const Math::PrefixOperator<Math::negate>& expr);
    double operator()(const Math::BinaryOperator<Math::add>& expr);
    double operator()(const Math::BinaryOperator<Math::subtract>& expr);
    double operator()(const Math::BinaryOperator<Math::multiply>& expr);
    double operator()(const Math::BinaryOperator<Math::divide>& expr);
    double operator()(const Math::BinaryOperator<Math::exponentiate>& expr);
    double operator()(const Math::CallOperator& expr);
    double operator()(const Math::SquareRoot& expr);
    double operator()(const Math::NthRoot& expr);
    double operator()(const Math::Sine& expr);
    double operator()(const Math::Cosine& expr);
    double operator()(const Math::Tangent& expr);
    double operator()(const Math::InverseSine& expr);
    double operator()(const Math::InverseCosine& expr);
    double operator()(const Math::InverseTangent& expr);
    double operator()(const Math::InverseTangent2& expr);
    double operator()(const Math::HyperbolicSine& expr);
    double operator()(const Math::HyperbolicCosine& expr);
    double operator()(const Math::HyperbolicTangent& expr);
    double operator()(const Math::InverseHyperbolicSine& expr);
    double operator()(const Math::InverseHyperbolicCosine& expr);
    double operator()(const Math::InverseHyperbolicTangent& expr);
    double operator()(const Math::Log10& expr);
    double operator()(const Math::Log2& expr);
    double operator()(const Math::NaturalLog& expr);
    double operator()(const Math::Logarithm& expr);
    double operator()(const Math::Exp& expr);
    
private:
    std::unordered_map<std::string_view, Math::NumberReferenceAssignmentDeclaration> m_number_references;
    std::unordered_map<std::string_view, Math::FunctionReferenceAssignmentDeclaration> m_function_references;
};

} /* namespace Calc */

#endif /* Calculator_hpp */
