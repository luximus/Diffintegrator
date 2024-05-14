//
//  Declaration.hpp
//  Diffintegrator
//
//  Created by Ivan on 5/5/24.
//

#ifndef Declaration_hpp
#define Declaration_hpp

// Redefine the maximum number of types in a variant
#define BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS
#define BOOST_MPL_LIMIT_LIST_SIZE 50

#include <vector>
#include <boost/functional/hash.hpp>
#include <boost/variant.hpp>

#include "Expression.hpp"

namespace Math {

/**
 A declaration that simply contains a mathematical expression.
 */
class ExpressionDeclaration {
    Expression m_expr;
    
public:
    ExpressionDeclaration(Expression expr)
    : m_expr(expr) {}
    
    const Expression& expr() const { return m_expr; }
    
    friend bool operator==(const ExpressionDeclaration& lhs, const ExpressionDeclaration& rhs);
};

bool operator==(const ExpressionDeclaration& lhs, const ExpressionDeclaration& rhs);

/**
 A declaration that assigns a number reference.
 */
class NumberReferenceAssignmentDeclaration {
    NumberReference m_ref;
    Expression m_expr;
    
public:
    NumberReferenceAssignmentDeclaration(NumberReference ref, Expression expr)
    : m_ref(ref), m_expr(expr) {}
    
    const NumberReference& ref() const { return m_ref; }
    const Expression& expr() const { return m_expr; }
};

/**
 A declaration that assigns a function reference.
 */
class FunctionReferenceAssignmentDeclaration {
    FunctionReference m_ref;
    std::vector<Variable> m_args;
    Expression m_expr;
    
public:
    FunctionReferenceAssignmentDeclaration(FunctionReference ref, std::vector<Variable> args, Expression expr)
    : m_ref(ref), m_args(args), m_expr(expr) {}
    
    const FunctionReference& ref() const { return m_ref; }
    const std::vector<Variable>& args() const { return m_args; }
    const Expression& expr() const { return m_expr; }
};

/**
 An explicit equation involving variables.
 */
class ExplicitEquationDeclaration {
    Variable m_assignee;
    Expression m_expr;
    
public:
    ExplicitEquationDeclaration(Variable assignee, Expression expr)
    : m_assignee(assignee), m_expr(expr) {}
    
    const Variable& assignee() const { return m_assignee; }
    const Expression& expr() const { return m_expr; }
};

typedef boost::variant<
    ExpressionDeclaration,
    NumberReferenceAssignmentDeclaration,
    FunctionReferenceAssignmentDeclaration,
    ExplicitEquationDeclaration
> Declaration;

} /* namespace Math */

#endif /* Declaration_hpp */
