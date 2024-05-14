//
//  Environment.cpp
//  Diffintegrator
//
//  Created by Ivan on 5/5/24.
//

#include <format>
#include <memory>
#include <utility>
#include <boost/variant/get.hpp>
#include <boost/variant/apply_visitor.hpp>

#include "Environment.hpp"
#include "Declaration.hpp"
#include "DependencyExtractor.hpp"
#include "Exceptions.hpp"

const std::shared_ptr<Math::Environment::DeclarationNode> Math::Environment::add_declaration(Declaration decl) noexcept(false) {
    const std::shared_ptr<DeclarationNode> node = std::make_shared<DeclarationNode>(DeclarationNode(decl));
    if (NumberReferenceAssignmentDeclaration* num_decl = boost::get<NumberReferenceAssignmentDeclaration>(&decl)) {
        if (!m_number_refs.contains(num_decl->ref())) {
            throw Math::ReferenceError(std::format("repeated assignment to number reference \"{0}\"", num_decl->ref().name).c_str());
        }
        m_number_refs.insert(std::make_pair(num_decl->ref(), node));
    } else if (FunctionReferenceAssignmentDeclaration* func_decl = boost::get<FunctionReferenceAssignmentDeclaration>(&decl)) {
        if (!m_function_refs.contains(func_decl->ref())) {
            throw Math::ReferenceError(std::format("repeated assignment to function reference \"{0}\"", func_decl->ref().name).c_str());
        }
        m_function_refs.insert(std::make_pair(func_decl->ref(), node));
    }
    m_declarations.insert(node);
    return node;
}

void Math::Environment::remove_declaration(std::shared_ptr<Math::Environment::DeclarationNode> node) {
    m_declarations.erase(node);
    if (const Math::NumberReferenceAssignmentDeclaration* num_decl = boost::get<Math::NumberReferenceAssignmentDeclaration>(&(node->get()))) {
        m_number_refs.erase(num_decl->ref());
    } else if (const Math::FunctionReferenceAssignmentDeclaration* func_decl = boost::get<Math::FunctionReferenceAssignmentDeclaration>(&(node->get()))) {
        m_function_refs.erase(func_decl->ref());
    }
}

template <typename result_type>
result_type visit(std::shared_ptr<Math::Environment::DeclarationNode> node,
                  boost::static_visitor<result_type>& visitor,
                  std::set<const std::shared_ptr<Math::Environment::DeclarationNode>, result_type>& result,
                  Math::Environment* env,
                  Math::Environment::NodeSet& not_visited,
                  Math::Environment::NodeSet& visited,
                  Math::Environment::NodeSet& done) noexcept(false) {
    if (done.contains(node)) {
        return;
    } else if (visited.contains(node)) {
        throw Math::ReferenceError("reference cycle detected");
    }
    
    not_visited.erase(node);
    visited.insert(node);
    
    std::for_each(node->number_ref_dependencies().begin(), node->number_ref_dependencies().end(),
                  [&](Math::NumberReference ref) {
        visit(env->get_reference_assignment_node(ref), visitor, env, not_visited, visited, done);
    });
    
    std::for_each(node->function_ref_dependencies().begin(), node->function_ref_dependencies().end(),
                  [&](Math::FunctionReference ref) {
        visit(env->get_reference_assignment_node(ref), visitor, env, not_visited, visited, done);
    });
    
    done.insert(node);
    result[node] = boost::apply_visitor(visitor, node->get());
}

template <typename result_type>
std::map<const std::shared_ptr<Math::Environment::DeclarationNode>, result_type> Math::Environment::eval(boost::static_visitor<result_type>& visitor) const noexcept(false) {
    NodeSet not_visited(m_declarations);
    NodeSet visited;
    NodeSet done;
    std::map<const std::shared_ptr<Math::Environment::DeclarationNode>, result_type> result;
    
    while (!not_visited.empty()) {
        visit(*not_visited.cbegin(), this, visitor, not_visited, visited, done);
    }
    
    return result;
}

void Math::Environment::DeclarationNode::calc_dependencies() {
    Math::DependencyExtractor ref_extractor;
    ref_extractor.extract_from(m_decl);
    Math::DependencyExtractor::Result extractor_result = ref_extractor.result();
    
    m_number_ref_dependencies.insert(extractor_result.number_refs.begin(), extractor_result.number_refs.end());
    m_function_ref_dependencies.insert(extractor_result.function_refs.begin(), extractor_result.function_refs.end());
    m_variable_dependencies.insert(extractor_result.variables.begin(), extractor_result.variables.end());
}
