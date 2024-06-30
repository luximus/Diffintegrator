//
//  main.cpp
//  DiffintegratorBackendPlayground
//
//  Created by Ivan on 4/3/24.
//

#include <iostream>
#include <numbers>
#include <string>

#include "Dual.hpp"
#include "Environment.hpp"
#include "Expression.hpp"
#include "Evaluator.hpp"

Math::Dual f(Math::Dual x) {
    return atan2(sin(x), 2 * cos(x));
}

int main(int argc, const char * argv[]) {
    Math::Environment::SharedPtr env = Math::make_environment();
    Math::EnvironmentNodeSharedPtr node1 = std::make_shared<Math::EnvironmentNode>(Math::ExpressionNode(
        Math::BinaryOperator<Math::add>(Math::BinaryOperator<Math::exponentiate>(Math::NumberReference("x"), 2), 1)
    ));
    env->add_node(node1);
    Math::EnvironmentNodeSharedPtr node2 = std::make_shared<Math::EnvironmentNode>(Math::ExpressionNode(
        Math::Dual::variable(5)
    ));
    env->assign(Math::NumberReference("x"), node2);
    
    Math::Evaluator calc(env);
    auto results = calc.eval_all_in_environment();
    std::cout << "The result is " << std::string(results.at(node1)) << std::endl;
    return 0;
}
