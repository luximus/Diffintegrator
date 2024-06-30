//
//  Evaluator.cpp
//  Diffintegrator
//
//  Created by Ivan on 4/3/24.
//

// Redefine the maximum number of types in a variant
#define BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS
#define BOOST_MPL_LIMIT_LIST_SIZE 50

#include <exception>
#include <functional>
#include <utility>
#include <vector>

#include <boost/variant/apply_visitor.hpp>
#include <boost/variant/static_visitor.hpp>

#include "Dual.hpp"
#include "Evaluator.hpp"
#include "Expression.hpp"

class ExpressionEvaluator : public boost::static_visitor<Math::Dual> {
public:
    
    ExpressionEvaluator(const std::shared_ptr<Math::Evaluator::GlobalContext> global_context,
                        const std::map<Math::Variable, Math::Dual>&& local_variables)
    : m_global_context(global_context), m_local_variables(local_variables) {}
    
    ExpressionEvaluator(const std::shared_ptr<Math::Evaluator::GlobalContext> global_context)
    : m_global_context(global_context) {}
    
    Math::Dual operator()(const Math::Dual& value) {
        return value;
    }
    
    Math::Dual operator()(const Math::NumberReference& expr) {
        return m_global_context->number_references.at(expr);
    }
    
//    Math::Dual operator()(const Math::FunctionReference& expr) {
//        throw std::logic_error("Function references not yet supported");
//    }
    
    Math::Dual operator()(const Math::Variable& expr) {
        return m_local_variables.at(expr);
    }
    
    Math::Dual operator()(const Math::PrefixOperator<Math::negate>& expr) {
        return -boost::apply_visitor(*this, expr.argument);
    }

    Math::Dual operator()(const Math::BinaryOperator<Math::add>& expr) {
        return boost::apply_visitor(*this, expr.left) + boost::apply_visitor(*this, expr.right);
    }

    Math::Dual operator()(const Math::BinaryOperator<Math::subtract>& expr) {
        return boost::apply_visitor(*this, expr.left) - boost::apply_visitor(*this, expr.right);
    }

    Math::Dual operator()(const Math::BinaryOperator<Math::multiply>& expr) {
        return boost::apply_visitor(*this, expr.left) * boost::apply_visitor(*this, expr.right);
    }

    Math::Dual operator()(const Math::BinaryOperator<Math::divide>& expr) {
        return boost::apply_visitor(*this, expr.left) / boost::apply_visitor(*this, expr.right);
    }

    Math::Dual operator()(const Math::BinaryOperator<Math::exponentiate>& expr) {
        return pow(boost::apply_visitor(*this, expr.left), boost::apply_visitor(*this, expr.right));
    }

//    Math::Dual operator()(const Math::CallOperator& expr) noexcept(false) {
//        std::vector<double> args;
//        for (const Math::Expression& arg : expr.args) {
//            args.push_back(boost::apply_visitor(*this, arg));
//        }
//        return m_global_context.function_references.at(expr.func)(args);
//    }

    Math::Dual operator()(const Math::SquareRoot& expr) {
        return sqrt(boost::apply_visitor(*this, expr.argument()));
    }

    Math::Dual operator()(const Math::NthRoot& expr) {
        return pow(boost::apply_visitor(*this, expr.argument<1>()),
                   1.0 / boost::apply_visitor(*this, expr.argument<0>()));
    }

    Math::Dual operator()(const Math::Sine& expr) {
        return sin(boost::apply_visitor(*this, expr.argument()));
    }

    Math::Dual operator()(const Math::Cosine& expr) {
        return cos(boost::apply_visitor(*this, expr.argument()));
    }

    Math::Dual operator()(const Math::Tangent& expr) {
        return tan(boost::apply_visitor(*this, expr.argument()));
    }

    Math::Dual operator()(const Math::InverseSine& expr) {
        return asin(boost::apply_visitor(*this, expr.argument()));
    }

    Math::Dual operator()(const Math::InverseCosine& expr) {
        return acos(boost::apply_visitor(*this, expr.argument()));
    }

    Math::Dual operator()(const Math::InverseTangent& expr) {
        return atan(boost::apply_visitor(*this, expr.argument()));
    }

    Math::Dual operator()(const Math::InverseTangent2& expr) {
        return atan2(boost::apply_visitor(*this, expr.argument<0>()),
                     boost::apply_visitor(*this, expr.argument<1>()));
    }

    Math::Dual operator()(const Math::HyperbolicSine& expr) {
        return sinh(boost::apply_visitor(*this, expr.argument()));
    }

    Math::Dual operator()(const Math::HyperbolicCosine& expr) {
        return cosh(boost::apply_visitor(*this, expr.argument()));
    }

    Math::Dual operator()(const Math::HyperbolicTangent& expr) {
        return tanh(boost::apply_visitor(*this, expr.argument()));
    }

    Math::Dual operator()(const Math::InverseHyperbolicSine& expr) {
        return asinh(boost::apply_visitor(*this, expr.argument()));
    }

    Math::Dual operator()(const Math::InverseHyperbolicCosine& expr) {
        return acosh(boost::apply_visitor(*this, expr.argument()));
    }

    Math::Dual operator()(const Math::InverseHyperbolicTangent& expr) {
        return atanh(boost::apply_visitor(*this, expr.argument()));
    }

    Math::Dual operator()(const Math::Log10& expr) {
        return log10(boost::apply_visitor(*this, expr.argument()));
    }

    Math::Dual operator()(const Math::Log2& expr) {
        return log2(boost::apply_visitor(*this, expr.argument()));
    }

    Math::Dual operator()(const Math::NaturalLog& expr) {
        return log(boost::apply_visitor(*this, expr.argument()));
    }

    Math::Dual operator()(const Math::Logarithm& expr) {
        return log(boost::apply_visitor(*this, expr.argument<1>()))
               / log(boost::apply_visitor(*this, expr.argument<0>()));
    }

    Math::Dual operator()(const Math::Exp& expr) {
        return exp(boost::apply_visitor(*this, expr.argument()));
    }

private:
    
    const std::shared_ptr<Math::Evaluator::GlobalContext> m_global_context;
    const std::map<Math::Variable, Math::Dual> m_local_variables;
    
};

Math::Dual Math::Evaluator::operator()(const ExpressionNode& node, const std::shared_ptr<Evaluator::GlobalContext> context) const {
    for (const NumberReference& ref : node.number_ref_dependencies()) {
        if (!context->number_references.contains(ref)) {
            EnvironmentNodeCSharedPtr dep_node(m_env->get_assigned_node(ref));
            Math::Dual result = eval(dep_node, context);
            context->number_references.insert(std::make_pair(ref, result));
        }
    }
    
//    for (const FunctionReference& ref : node.function_ref_dependencies()) {
//        if (!context.function_references.contains(ref)) {
//            EnvironmentNodeCSharedPtr dep_node(m_env->get_assigned_node(ref));
//            eval(dep_node, context);
//        }
//    }
    
    ExpressionEvaluator evaler(context);
    return boost::apply_visitor(evaler, node.expr());
}
