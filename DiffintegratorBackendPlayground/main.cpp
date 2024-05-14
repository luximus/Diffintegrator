//
//  main.cpp
//  DiffintegratorBackendPlayground
//
//  Created by Ivan on 4/3/24.
//

#include <iostream>

#include <boost/variant/apply_visitor.hpp>

#include "Expression.hpp"
#include "Calculator.hpp"

int main(int argc, const char * argv[]) {
    Math::Expression expr = Math::BinaryOperator<Math::divide>(
        Math::BinaryOperator<Math::add>(Math::BinaryOperator<Math::multiply>(3, 2), 5),
        Math::BinaryOperator<Math::subtract>(Math::BinaryOperator<Math::exponentiate>(2, 5), 10));
    Math::Calculator calculator;
    double result = boost::apply_visitor(calculator, expr);
    std::cout << result << std::endl;
    return 0;
}
