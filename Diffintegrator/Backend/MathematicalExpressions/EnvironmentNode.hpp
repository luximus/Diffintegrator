//
//  EnvironmentNode.hpp
//  Diffintegrator
//
//  Created by Ivan on 5/5/24.
//

#ifndef EnvironmentNode_hpp
#define EnvironmentNode_hpp

// Redefine the maximum number of types in a variant
#define BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS
#define BOOST_MPL_LIMIT_LIST_SIZE 50

#include <memory>
#include <set>

#include "Expression.hpp"

namespace Math {

/**
 A declaration that simply contains a mathematical expression.
 */
class ExpressionNode {
    Expression m_expr;
    
    std::set<NumberReference> m_number_ref_dependencies;
//    std::set<FunctionReference> m_function_ref_dependencies;
    std::set<Variable> m_local_variable_dependencies;
    
    void calc_dependencies();
    
public:
    
    ExpressionNode(Expression expr)
    : m_expr(expr) {
        calc_dependencies();
    }
    
    const Expression& expr() const { return m_expr; }
    const std::set<NumberReference>& number_ref_dependencies() const { return m_number_ref_dependencies; }
//    const std::set<FunctionReference>& function_ref_dependencies() const { return m_function_ref_dependencies; }

};

typedef boost::variant<
    ExpressionNode
> EnvironmentNode;

using EnvironmentNodeSharedPtr = std::shared_ptr<EnvironmentNode>;
using EnvironmentNodeCSharedPtr = const std::shared_ptr<EnvironmentNode>;

} /* namespace Math */

#endif /* EnvironmentNode_hpp */
