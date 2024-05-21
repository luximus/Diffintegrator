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

//#include <vector>
#include <compare>

#include <boost/variant/variant.hpp>
#include <boost/variant/recursive_wrapper.hpp>
#include <boost/fusion/include/vector.hpp>
#include <boost/fusion/include/at_c.hpp>

#include "TypeUtil.hpp"

namespace fusion = boost::fusion;

namespace Math {

/**
 A reference a numerical value.
 */
struct NumberReference {
    std::string_view name;
    
//    NumberReference(std::string name) : name(name) {};
    NumberReference(std::string_view name) : name(name) {};
    
    friend auto operator<=>(const NumberReference&, const NumberReference&) = default;
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
    
    friend auto operator<=>(const FunctionReference&, const FunctionReference&) = default;
};

/**
 A variable.
 */
struct Variable {
    std::string_view name;
    
    Variable(std::string name) : name(name) {}
    Variable(std::string_view name) : name(name) {}
    
    friend auto operator<=>(const Variable&, const Variable& rhs) = default;
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

///**
// An operator for calling a function.
// */
//struct CallOperator;

/**
 Function operators.
 */
template <typename... arg_types>
class FunctionOperator {
private:
    fusion::vector<arg_types...> m_arguments;

public:
    FunctionOperator(const arg_types&... args)
    : m_arguments(fusion::vector<arg_types...>(args...)) {}
    
    const fusion::vector<arg_types...>& arguments() const {
        return m_arguments;
    }
    
    template <int arg_index>
    const NthTypeOf<arg_index, arg_types...>& argument() const {
        using fusion::at_c;
        return at_c<arg_index>(m_arguments);
    }
};

template <typename arg_type>
class FunctionOperator<arg_type> {
private:
    arg_type m_argument;
    
public:
    FunctionOperator(const arg_type& arg)
    : m_argument(arg) {}
    
    const arg_type& argument() const {
        return m_argument;
    }
};

/**
 Square root.
 */
class SquareRoot;

/**
 Nth root.
 */
class NthRoot;

/**
 Sine.
 */
class Sine;

/**
 Cosine.
 */
class Cosine;

/**
 Tangent.
 */
class Tangent;

/**
 Inverse sine (arcsine).
 */
class InverseSine;

/**
 Inverse cosine (arccosine).
 */
class InverseCosine;

/**
 Inverse tangent (arctangent).
 */
class InverseTangent;

/**
 Two parameter inverse tangent.
 */
class InverseTangent2;

/**
 Hyperbolic sine.
 */
class HyperbolicSine;

/**
 Hyperbolic cosine.
 */
class HyperbolicCosine;

/**
 Hyperbolic tangent.
 */
class HyperbolicTangent;

/**
 Inverse hyperbolic sine.
 */
class InverseHyperbolicSine;

/**
 Inverse hyperbolic cosine.
 */
class InverseHyperbolicCosine;

/**
 Inverse hyperbolic tangent.
 */
class InverseHyperbolicTangent;

/**
 Base 10 logarithm.
 */
class Log10;

/**
 Base 2 logarithm.
 */
class Log2;

/**
 Natural logarithm (base *e*).
 */
class NaturalLog;

/**
 Arbitrary-base logarithm.
 */
class Logarithm;

/**
 Natural exponent (*e*^x).
 */
class Exp;

typedef boost::variant<
    double,
    NumberReference,
    Variable,
    boost::recursive_wrapper<PrefixOperator<negate>>,
    boost::recursive_wrapper<BinaryOperator<add>>,
    boost::recursive_wrapper<BinaryOperator<subtract>>,
    boost::recursive_wrapper<BinaryOperator<multiply>>,
    boost::recursive_wrapper<BinaryOperator<divide>>,
    boost::recursive_wrapper<BinaryOperator<exponentiate>>,
//    boost::recursive_wrapper<CallOperator>,
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
    boost::recursive_wrapper<Logarithm>,
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

//struct CallOperator {
//    FunctionReference func;
//    std::vector<Expression> args;
//    
//    CallOperator(const FunctionReference& func, const std::vector<Expression>& args) noexcept(false)
//    : func(func), args(args) {
//        if (args.size() != func.number_of_arguments) {
//            throw std::logic_error("Claimed number of arguments does not match actual number");  // TODO: Add exception here
//        };
//    }
//};

class SquareRoot : public FunctionOperator<Expression> {
public:
    using FunctionOperator<Expression>::FunctionOperator;
    static constexpr std::string_view name = "sqrt";
};

/**
 Nth root.
 */
class NthRoot : public FunctionOperator<Expression, Expression> {
public:
    using FunctionOperator<Expression, Expression>::FunctionOperator;
    static constexpr std::string_view name = "nthroot";
};

/**
 Sine.
 */
class Sine : public FunctionOperator<Expression> {
public:
    using FunctionOperator<Expression>::FunctionOperator;
    static constexpr std::string_view name = "sin";
};

/**
 Cosine.
 */
class Cosine : public FunctionOperator<Expression> {
public:
    using FunctionOperator<Expression>::FunctionOperator;
    static constexpr std::string_view name = "cos";
};

/**
 Tangent.
 */
class Tangent : public FunctionOperator<Expression> {
public:
    using FunctionOperator<Expression>::FunctionOperator;
    static constexpr std::string_view name = "tan";
};

/**
 Inverse sine (arcsine).
 */
class InverseSine : public FunctionOperator<Expression> {
public:
    using FunctionOperator<Expression>::FunctionOperator;
    static constexpr std::string_view name = "asin";
};

/**
 Inverse cosine (arccosine).
 */
class InverseCosine : public FunctionOperator<Expression> {
public:
    using FunctionOperator<Expression>::FunctionOperator;
    static constexpr std::string_view name = "acos";
};

/**
 Inverse tangent (arctangent).
 */
class InverseTangent : public FunctionOperator<Expression> {
public:
    using FunctionOperator<Expression>::FunctionOperator;
    static constexpr std::string_view name = "atan";
};

/**
 Two parameter inverse tangent.
 */
class InverseTangent2 : public FunctionOperator<Expression, Expression> {
public:
    using FunctionOperator<Expression, Expression>::FunctionOperator;
    static constexpr std::string_view name = "atan2";
};

/**
 Hyperbolic sine.
 */
class HyperbolicSine : public FunctionOperator<Expression> {
public:
    using FunctionOperator<Expression>::FunctionOperator;
    static constexpr std::string_view name = "sinh";
};

/**
 Hyperbolic cosine.
 */
class HyperbolicCosine : public FunctionOperator<Expression> {
public:
    using FunctionOperator<Expression>::FunctionOperator;
    static constexpr std::string_view name = "cosh";
};

/**
 Hyperbolic tangent.
 */
class HyperbolicTangent : public FunctionOperator<Expression> {
public:
    using FunctionOperator<Expression>::FunctionOperator;
    static constexpr std::string_view name = "tanh";
};

/**
 Inverse hyperbolic sine.
 */
class InverseHyperbolicSine : public FunctionOperator<Expression> {
public:
    using FunctionOperator<Expression>::FunctionOperator;
    static constexpr std::string_view name = "asinh";
};

/**
 Inverse hyperbolic cosine.
 */
class InverseHyperbolicCosine : public FunctionOperator<Expression> {
public:
    using FunctionOperator<Expression>::FunctionOperator;
    static constexpr std::string_view name = "acosh";
};

/**
 Inverse hyperbolic tangent.
 */
class InverseHyperbolicTangent : public FunctionOperator<Expression> {
public:
    using FunctionOperator<Expression>::FunctionOperator;
    static constexpr std::string_view name = "atanh";
};

/**
 Base 10 logarithm.
 */
class Log10 : public FunctionOperator<Expression> {
public:
    using FunctionOperator<Expression>::FunctionOperator;
    static constexpr std::string_view name = "log10";
};

/**
 Base 2 logarithm.
 */
class Log2 : public FunctionOperator<Expression> {
public:
    using FunctionOperator<Expression>::FunctionOperator;
    static constexpr std::string_view name = "log2";
};

/**
 Natural logarithm (base *e*).
 */
class NaturalLog : public FunctionOperator<Expression> {
public:
    using FunctionOperator<Expression>::FunctionOperator;
    static constexpr std::string_view name = "ln";
};

/**
 Arbitrary-base logarithm.
 */
class Logarithm : public FunctionOperator<Expression, Expression> {
public:
    using FunctionOperator<Expression, Expression>::FunctionOperator;
    static constexpr std::string_view name = "log";
};

/**
 Natural exponent (*e*^x).
 */
class Exp : public FunctionOperator<Expression> {
public:
    using FunctionOperator<Expression>::FunctionOperator;
    static constexpr std::string_view name = "exp";
};

} /* namespace Math */

#endif /* Expression_hpp */
