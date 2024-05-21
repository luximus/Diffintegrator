//
//  main.cpp
//  DiffintegratorBackendPlayground
//
//  Created by Ivan on 4/3/24.
//

#include <iostream>

#include "Environment.hpp"
#include "Expression.hpp"
#include "Evaluator.hpp"


int main(int argc, const char * argv[]) {
    Math::Environment::SharedPtr env = Math::make_environment();
    Math::EnvironmentNodeSharedPtr node1 = std::make_shared<Math::EnvironmentNode>(Math::ExpressionNode(Math::BinaryOperator<Math::add>(1, 1)));
    env->add_node(node1);
    env->assign(Math::NumberReference("x"), node1);
    Math::EnvironmentNodeSharedPtr node2 = std::make_shared<Math::EnvironmentNode>(Math::ExpressionNode(Math::BinaryOperator<Math::divide>(Math::NumberReference("x"), 2)));
    env->add_node(node2);
    Math::Evaluator calc(env);
    auto results = calc.eval_all_in_environment();
    std::cout << results.at(node2) << std::endl;
    return 0;
}
