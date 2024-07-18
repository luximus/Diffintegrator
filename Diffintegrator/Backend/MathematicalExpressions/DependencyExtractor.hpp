//
//  DependencyExtractor.hpp
//  Diffintegrator
//
//  Created by Ivan on 5/6/24.
//

#ifndef DependencyExtractor_hpp
#define DependencyExtractor_hpp

#include <set>

#include <boost/fusion/algorithm/iteration/for_each.hpp>
#include <boost/variant/static_visitor.hpp>
#include <boost/variant/apply_visitor.hpp>

#include "Dual.hpp"
#include "Expression.hpp"

namespace Math {

class DependencyExtractor : public boost::static_visitor<void> {
public:
    
    struct Result {
        std::set<NumberReference> number_refs;
        std::set<Variable> variables;
    };
    
private:
    
    Result m_result;
    
public:
    
    void extract_from(const Expression& expr) {
        boost::apply_visitor(*this, expr);
    }
    
    void operator()(const Dual& value) {}
    
    void operator()(const NumberReference& expr);
    
    void operator()(const Variable& expr);
    
    template <PrefixOperatorTags tag>
    void operator()(const PrefixOperator<tag>& expr) {
        boost::apply_visitor(*this, expr.argument);
    }
    
    template <BinaryOperatorTags tag>
    void operator()(const BinaryOperator<tag>& expr) {
        boost::apply_visitor(*this, expr.left);
        boost::apply_visitor(*this, expr.right);
    }
    
//    void operator()(const Math::CallOperator& expr);
    
    template <typename... arg_types>
    void operator()(const FunctionOperator<arg_types...>& expr) {
        boost::fusion::for_each(expr.arguments(), [&]<typename T>(const T& arg) {
            boost::apply_visitor(*this, arg);
        });
    }
    
    template <typename arg_type>
    void operator()(const FunctionOperator<arg_type>& expr) {
        boost::apply_visitor(*this, expr.argument());
    }
    
    const Result& result() const { return m_result; }
    
};

} /* namespace Math */

#endif /* DependencyExtractor_hpp */
