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
#include <utility>

#include "EnvironmentNode.hpp"
#include "Expression.hpp"

namespace Math {

/**
 A mathematical environment for evaluating mathematical expressions.
 */
class Environment : public std::enable_shared_from_this<Environment> {
    
public:
    
    using SharedPtr = std::shared_ptr<Environment>;
    using WeakPtr = std::weak_ptr<Environment>;
    
    friend Environment::SharedPtr make_environment();
    
    /**
     Get a shared pointer to this `Environment`.
     */
    std::shared_ptr<Environment> getptr() {
        return shared_from_this();
    }
    
    /**
     Get a weak pointer to this `Environment`.
     */
    Environment::WeakPtr getweakptr() {
        return weak_from_this();
    }
    
    /**
     A set of constant shared pointers to `EnvironmentNode`s.
     */
    typedef std::set<EnvironmentNodeCSharedPtr> NodeSet;
    
    /**
     Get the nodes currently in this environment.
     */
    const NodeSet& nodes() const { return m_nodes; }
    
    /**
     Add a new node to this environment.
     */
    void add_node(EnvironmentNodeSharedPtr node) noexcept(false);
    
    /**
     Remove a node from this environment.
     */
    void remove_node(EnvironmentNodeSharedPtr node);
    
    /**
     Get a shared pointer to the `EnvironmentNode` that assigns the given number reference.
     */
    EnvironmentNodeCSharedPtr get_assigned_node(NumberReference ref) const {
        return m_number_refs.at(ref);
    }
    
    void assign(NumberReference ref, EnvironmentNodeSharedPtr node) {
        m_number_refs.insert(std::make_pair(ref, node));
    }
    
private:
    
    NodeSet m_nodes;
    
    std::map<NumberReference, EnvironmentNodeCSharedPtr> m_number_refs;
    

};

Environment::SharedPtr make_environment();

} /* namespace Math */

#endif /* Environment_hpp */
