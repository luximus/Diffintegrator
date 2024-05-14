//
//  Environment.hpp
//  Diffintegrator
//
//  Created by Ivan on 5/5/24.
//

#ifndef Environment_hpp
#define Environment_hpp

#include <map>
#include <memory>
#include <set>
#include <string>
#include <vector>

#include <boost/variant/static_visitor.hpp>

#include "Expression.hpp"
#include "Declaration.hpp"

namespace Math {

class Environment {
public:
    
    class DeclarationNode;
    
private:
    
    using DeclarationNodeCSharedPtr = const std::shared_ptr<DeclarationNode>;
    
public:
    
    typedef std::set<DeclarationNodeCSharedPtr> NodeSet;
    
    DeclarationNodeCSharedPtr add_declaration(Declaration decl) noexcept(false);
    void remove_declaration(std::shared_ptr<DeclarationNode> node);
    
    DeclarationNodeCSharedPtr get_reference_assignment_node(NumberReference ref) {
        return m_number_refs.at(ref);
    }
    
    DeclarationNodeCSharedPtr get_reference_assignment_node(FunctionReference ref) {
        return m_function_refs.at(ref);
    }
    
    template <typename result_type>
    std::map<DeclarationNodeCSharedPtr, result_type> eval(boost::static_visitor<result_type>& visitor) const noexcept(false);
    
private:
    
    NodeSet m_declarations;
    
    std::map<NumberReference, DeclarationNodeCSharedPtr> m_number_refs;
    std::map<FunctionReference, DeclarationNodeCSharedPtr> m_function_refs;
    

};

class Environment::DeclarationNode {
public:
    
    DeclarationNode(Declaration decl) : m_decl(decl) {
        calc_dependencies();
    }
    
    const Declaration& get() const { return m_decl; }
    const std::set<NumberReference>& number_ref_dependencies() const { return m_number_ref_dependencies; }
    const std::set<FunctionReference>& function_ref_dependencies() const { return m_function_ref_dependencies; }
    const std::set<Variable>& variable_dependencies() const { return m_variable_dependencies; }
    
    
    
private:
    
    Declaration m_decl;
    std::set<NumberReference> m_number_ref_dependencies;
    std::set<FunctionReference> m_function_ref_dependencies;
    std::set<Variable> m_variable_dependencies;
    
    void calc_dependencies();
};

}  // namespace Math

#endif /* Environment_hpp */
