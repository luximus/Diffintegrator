//
//  Environment.cpp
//  Diffintegrator
//
//  Created by Ivan on 5/5/24.
//

#include "Environment.hpp"
#include "EnvironmentNode.hpp"

Math::Environment::SharedPtr Math::make_environment() {
    Environment::SharedPtr env = std::make_shared<Environment>();
    return env;
}

void Math::Environment::add_node(Math::EnvironmentNodeSharedPtr node) {
    m_nodes.insert(node);
}

void Math::Environment::remove_node(Math::EnvironmentNodeSharedPtr node) {
    m_nodes.erase(node);
}
