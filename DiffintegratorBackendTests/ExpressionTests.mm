//
//  ExpressionTests.mm
//  ExpressionTests
//
//  Created by Ivan on 4/3/24.
//

#import <XCTest/XCTest.h>

#include <numbers>

#include "Expression.hpp"
#include "Calculator.hpp"

@interface ExpressionTests : XCTestCase

@end

@implementation ExpressionTests

- (void)setUp {
    // Put setup code here. This method is called before the invocation of each test method in the class.
}

- (void)tearDown {
    // Put teardown code here. This method is called after the invocation of each test method in the class.
}

/**
 Check if an expression, when evaluated, is equal to the given expression.
 */
- (void)assertExpression:(Expr::Expression)expr equals:(double)expected {
    Calc::Calculator calculator;
    double result = boost::apply_visitor(calculator, expr);
    XCTAssertEqual(result, expected);
}

/**
 Check if an expression, when evaluated, is equal to the given expression within a given accuracy.
 */
- (void)assertExpression:(Expr::Expression)expr equals:(double)expected withAccuracy:(double)accuracy {
    Calc::Calculator calculator;
    double result = boost::apply_visitor(calculator, expr);
    XCTAssertEqualWithAccuracy(result, expected, accuracy);
}

- (void)testNegate {
    Expr::Expression expr = Expr::PrefixOperator<Expr::negate>(1);
    [self assertExpression:expr equals:-1];
}

- (void)testArithmeticExpression {
    Expr::Expression expr = Expr::BinaryOperator<Expr::divide>(
        Expr::BinaryOperator<Expr::add>(Expr::BinaryOperator<Expr::multiply>(3, 2), 5),
        Expr::BinaryOperator<Expr::subtract>(Expr::BinaryOperator<Expr::exponentiate>(2, 5), 10));
    [self assertExpression:expr equals:0.5 withAccuracy:1e-10];
}

- (void)testSquareRoot {
    Expr::Expression expr = Expr::SquareRoot(2);
    [self assertExpression:expr equals:sqrt(2)];
}

- (void)testNthRoot {
    Expr::Expression expr = Expr::NthRoot(3, 8);
    [self assertExpression:expr equals:2 withAccuracy:1e-10];
}

- (void)testSine {
    Expr::Expression expr = Expr::Sine(std::numbers::pi / 2);
    [self assertExpression:expr equals:1 withAccuracy:1e-10];
}

- (void)testCosine {
    Expr::Expression expr = Expr::Cosine(0);
    [self assertExpression:expr equals:1 withAccuracy:1e-10];
}

- (void)testTangent {
    Expr::Expression expr = Expr::Tangent(std::numbers::pi / 4);
    [self assertExpression:expr equals:1 withAccuracy:1e-10];
}

- (void)testInverseSine {
    Expr::Expression expr = Expr::InverseSine(1);
    [self assertExpression:expr equals:std::numbers::pi / 2 withAccuracy:1e-10];
}

- (void)testInverseCosine {
    Expr::Expression expr = Expr::InverseCosine(0);
    [self assertExpression:expr equals:std::numbers::pi / 2 withAccuracy:1e-10];
}

- (void)testInverseTangent {
    Expr::Expression expr = Expr::InverseTangent(1);
    [self assertExpression:expr equals:std::numbers::pi / 4 withAccuracy:1e-10];
}

- (void)testInverseTangent2 {
    Expr::Expression expr = Expr::InverseTangent2(0.5, sqrt(3) / 2);
    [self assertExpression:expr equals:std::numbers::pi / 6 withAccuracy:1e-10];
}

- (void)testHyperbolicSine {
    Expr::Expression expr = Expr::HyperbolicSine(1);
    [self assertExpression:expr equals:sinh(1)];
}

- (void)testHyperbolicCosine {
    Expr::Expression expr = Expr::HyperbolicCosine(1);
    [self assertExpression:expr equals:cosh(1)];
}

- (void)testHyperbolicTangent {
    Expr::Expression expr = Expr::HyperbolicTangent(1);
    [self assertExpression:expr equals:tanh(1)];
}

- (void)testInverseHyperbolicSine {
    Expr::Expression expr = Expr::InverseHyperbolicSine(1);
    [self assertExpression:expr equals:asinh(1)];
}

- (void)testInverseHyperbolicCosine {
    Expr::Expression expr = Expr::InverseHyperbolicCosine(1);
    [self assertExpression:expr equals:acosh(1)];
}

- (void)testInverseHyperbolicTangent {
    Expr::Expression expr = Expr::InverseHyperbolicTangent(1);
    [self assertExpression:expr equals:atanh(1)];
}

- (void)testLog10 {
    Expr::Expression expr = Expr::Log10(5);
    [self assertExpression:expr equals:log10(5)];
}

- (void)testLog2 {
    Expr::Expression expr = Expr::Log2(5);
    [self assertExpression:expr equals:log2(5)];
}

- (void)testNaturalLog {
    Expr::Expression expr = Expr::NaturalLog(5);
    [self assertExpression:expr equals:log(5)];
}

- (void)testLog {
    Expr::Expression expr = Expr::Logarithm(3, 5);
    [self assertExpression:expr equals:log(5) / log(3)];
}

- (void)testExp {
    Expr::Expression expr = Expr::Exp(5);
    [self assertExpression:expr equals:exp(5)];
}

//- (void)testPerformanceExample {
//    // This is an example of a performance test case.
//    [self measureBlock:^{
//        // Put the code you want to measure the time of here.
//    }];
//}

@end
