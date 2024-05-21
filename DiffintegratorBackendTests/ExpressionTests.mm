//
//  ExpressionTests.mm
//  ExpressionTests
//
//  Created by Ivan on 4/3/24.
//

#import <XCTest/XCTest.h>

#include <numbers>

#include "Expression.hpp"
#include "Evaluator.hpp"

@interface ExpressionTests : XCTestCase

@end

@implementation ExpressionTests

- (void)setUp {
    // Put setup code here. This method is called before the invocation of each test method in the class.
}

- (void)tearDown {
    // Put teardown code here. This method is called after the invocation of each test method in the class.
}

///**
// Check if an expression, when evaluated, is equal to the given value.
// */
//- (void)assertExpression:(Math::Expression)expr equals:(double)expected {
//    Math::Evaluator calculator;
//    double result = boost::apply_visitor(calculator, expr);
//    XCTAssertEqual(result, expected);
//}
//
///**
// Check if an expression, when evaluated, is equal to the given expression within a given accuracy.
// */
//- (void)assertExpression:(Math::Expression)expr equals:(double)expected withAccuracy:(double)accuracy {
//    Math::Evaluator calculator;
//    double result = boost::apply_visitor(calculator, expr);
//    XCTAssertEqualWithAccuracy(result, expected, accuracy);
//}
//
//- (void)testNegate {
//    Math::Expression expr = Math::PrefixOperator<Math::negate>(1);
//    [self assertExpression:expr equals:-1];
//}
//
//- (void)testArithmeticExpression {
//    Math::Expression expr = Math::BinaryOperator<Math::divide>(
//        Math::BinaryOperator<Math::add>(Math::BinaryOperator<Math::multiply>(3, 2), 5),
//        Math::BinaryOperator<Math::subtract>(Math::BinaryOperator<Math::exponentiate>(2, 5), 10));
//    [self assertExpression:expr equals:0.5 withAccuracy:1e-10];
//}
//
//- (void)testSquareRoot {
//    Math::Expression expr = Math::SquareRoot(2);
//    [self assertExpression:expr equals:sqrt(2)];
//}
//
//- (void)testNthRoot {
//    Math::Expression expr = Math::NthRoot(3, 8);
//    [self assertExpression:expr equals:2 withAccuracy:1e-10];
//}
//
//- (void)testSine {
//    Math::Expression expr = Math::Sine(std::numbers::pi / 2);
//    [self assertExpression:expr equals:1 withAccuracy:1e-10];
//}
//
//- (void)testCosine {
//    Math::Expression expr = Math::Cosine(0);
//    [self assertExpression:expr equals:1 withAccuracy:1e-10];
//}
//
//- (void)testTangent {
//    Math::Expression expr = Math::Tangent(std::numbers::pi / 4);
//    [self assertExpression:expr equals:1 withAccuracy:1e-10];
//}
//
//- (void)testInverseSine {
//    Math::Expression expr = Math::InverseSine(1);
//    [self assertExpression:expr equals:std::numbers::pi / 2 withAccuracy:1e-10];
//}
//
//- (void)testInverseCosine {
//    Math::Expression expr = Math::InverseCosine(0);
//    [self assertExpression:expr equals:std::numbers::pi / 2 withAccuracy:1e-10];
//}
//
//- (void)testInverseTangent {
//    Math::Expression expr = Math::InverseTangent(1);
//    [self assertExpression:expr equals:std::numbers::pi / 4 withAccuracy:1e-10];
//}
//
//- (void)testInverseTangent2 {
//    Math::Expression expr = Math::InverseTangent2(0.5, sqrt(3) / 2);
//    [self assertExpression:expr equals:std::numbers::pi / 6 withAccuracy:1e-10];
//}
//
//- (void)testHyperbolicSine {
//    Math::Expression expr = Math::HyperbolicSine(1);
//    [self assertExpression:expr equals:sinh(1)];
//}
//
//- (void)testHyperbolicCosine {
//    Math::Expression expr = Math::HyperbolicCosine(1);
//    [self assertExpression:expr equals:cosh(1)];
//}
//
//- (void)testHyperbolicTangent {
//    Math::Expression expr = Math::HyperbolicTangent(1);
//    [self assertExpression:expr equals:tanh(1)];
//}
//
//- (void)testInverseHyperbolicSine {
//    Math::Expression expr = Math::InverseHyperbolicSine(1);
//    [self assertExpression:expr equals:asinh(1)];
//}
//
//- (void)testInverseHyperbolicCosine {
//    Math::Expression expr = Math::InverseHyperbolicCosine(1);
//    [self assertExpression:expr equals:acosh(1)];
//}
//
//- (void)testInverseHyperbolicTangent {
//    Math::Expression expr = Math::InverseHyperbolicTangent(1);
//    [self assertExpression:expr equals:atanh(1)];
//}
//
//- (void)testLog10 {
//    Math::Expression expr = Math::Log10(5);
//    [self assertExpression:expr equals:log10(5)];
//}
//
//- (void)testLog2 {
//    Math::Expression expr = Math::Log2(5);
//    [self assertExpression:expr equals:log2(5)];
//}
//
//- (void)testNaturalLog {
//    Math::Expression expr = Math::NaturalLog(5);
//    [self assertExpression:expr equals:log(5)];
//}
//
//- (void)testLog {
//    Math::Expression expr = Math::Logarithm(3, 5);
//    [self assertExpression:expr equals:log(5) / log(3)];
//}
//
//- (void)testExp {
//    Math::Expression expr = Math::Exp(5);
//    [self assertExpression:expr equals:exp(5)];
//}

//- (void)testPerformanceExample {
//    // This is an example of a performance test case.
//    [self measureBlock:^{
//        // Put the code you want to measure the time of here.
//    }];
//}

@end
