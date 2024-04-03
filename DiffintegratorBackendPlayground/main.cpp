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
    Expr::Expression expr = Expr::PrefixOperator<Expr::negate>(1);
    Calc::Calculator calculator;
    double result = boost::apply_visitor(calculator, expr);
    std::cout << result << std::endl;
    return 0;
}
