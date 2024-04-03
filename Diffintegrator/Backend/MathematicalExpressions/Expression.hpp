//
//  Expression.hpp
//  Diffintegrator
//
//  Created by Ivan on 3/4/24.
//

#ifndef Expression_hpp
#define Expression_hpp

// Redefine the maximum number of types in a variant
#define BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS
#define BOOST_MPL_LIMIT_LIST_SIZE 50

#include <vector>
#include <exception>

#include <boost/variant.hpp>
#include <boost/fusion/include/vector.hpp>

namespace fusion = boost::fusion;

namespace Expr {

/**
 A reference a numerical value.
 */
struct NumberReference {
    std::string_view name;
    
    NumberReference(std::string name) : name(name) {};
    NumberReference(std::string_view name) : name(name) {};
};

/**
 A reference to a function value.
 */
struct FunctionReference {
    std::string_view name;
    int number_of_arguments;
    
    FunctionReference(std::string name, int number_of_arguments)
    : name(name), number_of_arguments(number_of_arguments) {}
    
    FunctionReference(std::string_view name, int number_of_arguments)
    : name(name), number_of_arguments(number_of_arguments) {}
};

/**
 A variable.
 */
struct Variable {
    std::string_view name;
    
    Variable(std::string name) : name(name) {}
    Variable(std::string_view name) : name(name) {}
};

/**
 Tags for prefix unary operators.
 */
enum PrefixOperatorTags {
    negate
};

/**
 An arithmetic prefixed unary operator.
 */
template <PrefixOperatorTags OpTag>
struct PrefixOperator;

/**
 Tags for binary operators.
 */
enum BinaryOperatorTags {
    add,
    subtract,
    multiply,
    divide,
    exponentiate
};

/**
 An arithmetic binary operator.
 */
template <BinaryOperatorTags OpTag>
struct BinaryOperator;

/**
 An operator for calling a function.
 */
struct CallOperator;

/**
 Function operators.
 */
template <typename... arg_types>
class FunctionOperator {
    fusion::vector<arg_types...> m_arguments;

public:
    FunctionOperator(arg_types... args)
    : m_arguments(fusion::vector<arg_types...>(args...)) {}
    
    const fusion::vector<arg_types...>& arguments() const {
        return m_arguments;
    }
};

/**
 Square root.
 */
class SquareRoot : public FunctionOperator<double> {
    static constexpr std::string_view name = "sqrt";
};

/**
 Nth root.
 */
class NthRoot : public FunctionOperator<double, double> {
    static constexpr std::string_view name = "nthroot";
};

/**
 Sine.
 */
class Sine : public FunctionOperator<double> {
    static constexpr std::string_view name = "sin";
};

/**
 Cosine.
 */
class Cosine : public FunctionOperator<double> {
    static constexpr std::string_view name = "cos";
};

/**
 Tangent.
 */
class Tangent : public FunctionOperator<double> {
    static constexpr std::string_view name = "tan";
};

/**
 Inverse sine (arcsine).
 */
class InverseSine : public FunctionOperator<double> {
    static constexpr std::string_view name = "asin";
};

/**
 Inverse cosine (arccosine).
 */
class InverseCosine : public FunctionOperator<double> {
    static constexpr std::string_view name = "acos";
};

/**
 Inverse tangent (arctangent).
 */
class InverseTangent : public FunctionOperator<double> {
    static constexpr std::string_view name = "atan";
};

/**
 Two parameter inverse tangent.
 */
class InverseTangent2 : public FunctionOperator<double, double> {
    static constexpr std::string_view name = "atan2";
};

/**
 Hyperbolic sine.
 */
class HyperbolicSine : public FunctionOperator<double> {
    static constexpr std::string_view name = "sinh";
};

/**
 Hyperbolic cosine.
 */
class HyperbolicCosine : public FunctionOperator<double> {
    static constexpr std::string_view name = "cosh";
};

/**
 Hyperbolic tangent.
 */
class HyperbolicTangent : public FunctionOperator<double> {
    static constexpr std::string_view name = "tanh";
};

/**
 Inverse hyperbolic sine.
 */
class InverseHyperbolicSine : public FunctionOperator<double> {
    static constexpr std::string_view name = "asinh";
};

/**
 Inverse hyperbolic cosine.
 */
class InverseHyperbolicCosine : public FunctionOperator<double> {
    static constexpr std::string_view name = "acosh";
};

/**
 Inverse hyperbolic tangent.
 */
class InverseHyperbolicTangent : public FunctionOperator<double> {
    static constexpr std::string_view name = "atanh";
};

/**
 Base 10 logarithm.
 */
class Log10 : public FunctionOperator<double> {
    static constexpr std::string_view name = "log10";
};

/**
 Base 2 logarithm.
 */
class Log2 : public FunctionOperator<double> {
    static constexpr std::string_view name = "log2";
};

/**
 Natural logarithm (base *e*).
 */
class NaturalLog : public FunctionOperator<double> {
    static constexpr std::string_view name = "ln";
};

/**
 Arbitrary-base logarithm.
 */
class Logarithm : public FunctionOperator<double, double> {
    static constexpr std::string_view name = "log";
};

/**
 Natural exponent (*e*^x).
 */
class Exp : public FunctionOperator<double> {
    static constexpr std::string_view name = "exp";
};

typedef boost::variant<
    double,
    NumberReference,
    FunctionReference,
    Variable,
    boost::recursive_wrapper<PrefixOperator<negate>>,
    boost::recursive_wrapper<BinaryOperator<add>>,
    boost::recursive_wrapper<BinaryOperator<subtract>>,
    boost::recursive_wrapper<BinaryOperator<multiply>>,
    boost::recursive_wrapper<BinaryOperator<divide>>,
    boost::recursive_wrapper<BinaryOperator<exponentiate>>,
    boost::recursive_wrapper<CallOperator>,
    boost::recursive_wrapper<SquareRoot>,
    boost::recursive_wrapper<NthRoot>,
    boost::recursive_wrapper<Sine>,
    boost::recursive_wrapper<Cosine>,
    boost::recursive_wrapper<Tangent>,
    boost::recursive_wrapper<InverseSine>,
    boost::recursive_wrapper<InverseCosine>,
    boost::recursive_wrapper<InverseTangent>,
    boost::recursive_wrapper<InverseTangent2>,
    boost::recursive_wrapper<HyperbolicSine>,
    boost::recursive_wrapper<HyperbolicCosine>,
    boost::recursive_wrapper<HyperbolicTangent>,
    boost::recursive_wrapper<InverseHyperbolicSine>,
    boost::recursive_wrapper<InverseHyperbolicCosine>,
    boost::recursive_wrapper<InverseHyperbolicTangent>,
    boost::recursive_wrapper<Log10>,
    boost::recursive_wrapper<Log2>,
    boost::recursive_wrapper<NaturalLog>,
    boost::recursive_wrapper<Exp>
> Expression;

template <PrefixOperatorTags OpTag>
struct PrefixOperator {
    Expression argument;
    
    PrefixOperator(const Expression& arg)
    : argument(arg) {}
};

template <BinaryOperatorTags OpTag>
struct BinaryOperator {
    Expression left;
    Expression right;
    
    BinaryOperator(const Expression& lhs, const Expression& rhs)
    : left(lhs), right(rhs) {}
};

struct CallOperator {
    FunctionReference func;
    std::vector<Expression> args;
    
    CallOperator(const FunctionReference& func, const std::vector<Expression>& args) noexcept(false)
    : func(func), args(args) {
        if (args.size() != func.number_of_arguments) {
            throw "";  // TODO: Add exception here
        };
    }
};

} /* namespace Expr */

#endif /* Expression_hpp */
