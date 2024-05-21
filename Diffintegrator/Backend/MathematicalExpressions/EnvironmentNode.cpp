//
//  EnvironmentNode.cpp
//  Diffintegrator
//
//  Created by Ivan on 5/5/24.
//

#include "EnvironmentNode.hpp"

#include "DependencyExtractor.hpp"

void Math::ExpressionNode::calc_dependencies() {
    Math::DependencyExtractor ref_extractor;
    ref_extractor.extract_from(m_expr);
    Math::DependencyExtractor::Result extractor_result = ref_extractor.result();
    
    // TODO: Might not work, check later
    m_number_ref_dependencies.insert(extractor_result.number_refs.begin(), extractor_result.number_refs.end());
//    m_function_ref_dependencies.insert(extractor_result.function_refs.begin(), extractor_result.function_refs.end());
    m_local_variable_dependencies.insert(extractor_result.variables.begin(), extractor_result.variables.end());
}
