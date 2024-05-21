//
//  VariableExtractor.cpp
//  Diffintegrator
//
//  Created by Ivan on 5/6/24.
//

#include <boost/variant/apply_visitor.hpp>
#include <boost/fusion/algorithm/iteration/for_each.hpp>

#include "DependencyExtractor.hpp"

void Math::DependencyExtractor::operator()(const Math::NumberReference& expr) {
    m_result.number_refs.insert(expr);
}

void Math::DependencyExtractor::operator()(const Math::Variable& expr) {
    m_result.variables.insert(expr);
}

//void Math::DependencyExtractor::operator()(const Math::CallOperator& expr) {
//    m_result.function_refs.insert(expr.func);
//    
//    for (const Expression& arg : expr.args) {
//        boost::apply_visitor(*this, arg);
//    }
//}
