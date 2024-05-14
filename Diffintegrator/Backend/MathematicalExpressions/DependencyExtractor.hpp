//
//  DependencyExtractor.hpp
//  Diffintegrator
//
//  Created by Ivan on 5/6/24.
//

#ifndef DependencyExtractor_hpp
#define DependencyExtractor_hpp

#include <set>

#include <boost/variant/static_visitor.hpp>
#include <boost/variant/apply_visitor.hpp>

#include "Expression.hpp"
#include "Declaration.hpp"

namespace Math {

class DependencyExtractor : public boost::static_visitor<void> {
public:
    
    struct Result {
        std::set<NumberReference> number_refs;
        std::set<FunctionReference> function_refs;
        std::set<Variable> variables;
    };
    
private:
    
    Result m_result;
    
public:
    
    void extract_from(const Expression& expr) {
        boost::apply_visitor(*this, expr);
    }
    
    void extract_from(const Declaration& decl) {
        boost::apply_visitor(*this, decl);
    }
    
    void operator()(const double& value) {}
    
    void operator()(const Math::NumberReference& expr) {};
    void operator()(const Math::FunctionReference& expr) {};
    
    void operator()(const Math::Variable& expr);
    
    template <PrefixOperatorTags tag>
    void operator()(const Math::PrefixOperator<tag>& expr);
    
    template <BinaryOperatorTags tag>
    void operator()(const Math::BinaryOperator<tag>& expr);
    
    void operator()(const Math::CallOperator& expr);
    
    template <typename... arg_types>
    void operator()(const Math::FunctionOperator<arg_types...>& expr);
    
    template <typename arg_type>
    void operator()(const Math::FunctionOperator<arg_type>& expr);
    
    void operator()(const Math::ExpressionDeclaration& decl);
    
    void operator()(const Math::NumberReferenceAssignmentDeclaration& decl);
    
    void operator()(const Math::FunctionReferenceAssignmentDeclaration& decl);
    
    void operator()(const Math::ExplicitEquationDeclaration& decl);
    
    const Result& result() const { return m_result; }
    
};

} /* namespace Math */

#endif /* DependencyExtractor_hpp */
