//
//  VariableExtractor.cpp
//  Diffintegrator
//
//  Created by Ivan on 5/6/24.
//

#include <vector>

#include <boost/variant/apply_visitor.hpp>
#include <boost/fusion/algorithm/iteration/for_each.hpp>

#include "DependencyExtractor.hpp"

void Math::DependencyExtractor::operator()(const Math::Variable& expr) {
    m_result.variables.insert(expr);
}

template <Math::PrefixOperatorTags tag>
void Math::DependencyExtractor::operator()(const Math::PrefixOperator<tag>& expr) {
    boost::apply_visitor(*this, expr.argument);
}

template <Math::BinaryOperatorTags tag>
void Math::DependencyExtractor::operator()(const Math::BinaryOperator<tag>& expr) {
    boost::apply_visitor(*this, expr.left);
    boost::apply_visitor(*this, expr.right);
}

void Math::DependencyExtractor::operator()(const Math::CallOperator& expr) {
    m_result.function_refs.insert(expr.func);
    
    for (const Expression& arg : expr.args) {
        boost::apply_visitor(*this, arg);
    }
}

template <typename... arg_types>
void Math::DependencyExtractor::operator()(const Math::FunctionOperator<arg_types...>& expr) {
    boost::fusion::for_each(expr.arguments(), [&]<typename T>(const T& arg) {
        boost::apply_visitor(*this, arg);
    });
}

template <typename arg_type>
void Math::DependencyExtractor::operator()(const Math::FunctionOperator<arg_type>& expr) {
    boost::apply_visitor(*this, expr.argument());
}

void Math::DependencyExtractor::operator()(const Math::ExpressionDeclaration& decl) {
    boost::apply_visitor(*this, decl.expr());
}

void Math::DependencyExtractor::operator()(const Math::NumberReferenceAssignmentDeclaration& decl) {
    boost::apply_visitor(*this, decl.expr());
}

void Math::DependencyExtractor::operator()(const Math::FunctionReferenceAssignmentDeclaration& decl) {
    boost::apply_visitor(*this, decl.expr());
}

void Math::DependencyExtractor::operator()(const Math::ExplicitEquationDeclaration& decl) {
    m_result.variables.insert(decl.assignee());
    boost::apply_visitor(*this, decl.expr());
}
