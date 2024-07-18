//
//  Calculator.hpp
//  Diffintegrator
//
//  Created by Ivan on 5/18/24.
//

#ifndef Calculator_hpp
#define Calculator_hpp

// Redefine the maximum number of types in a variant
#define BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS
#define BOOST_MPL_LIMIT_LIST_SIZE 50

#include <map>
#include <memory>
#include <boost/variant/static_visitor.hpp>
#include <boost/variant/apply_visitor.hpp>
#include <boost/variant/variant.hpp>

#include "Dual.hpp"
#include "EnvironmentNode.hpp"
#include "Environment.hpp"
#include "Exceptions.hpp"
#include "Expression.hpp"

namespace Math {

template <typename result_type>
class Calculator : public boost::static_visitor<result_type> {
    
public:
    
    // MARK: Marking visits
    
    // May make this private
    class VisitMarker {
        std::set<EnvironmentNodeCSharedPtr> m_not_visited;
        std::set<EnvironmentNodeCSharedPtr> m_visited;
        std::set<EnvironmentNodeCSharedPtr> m_done;
        
    public:
        
        VisitMarker(std::set<EnvironmentNodeCSharedPtr> nodes) : m_not_visited(nodes) {};
        
        void mark(EnvironmentNodeCSharedPtr node) {
            m_not_visited.erase(node);
            m_visited.insert(node);
        }
        
        void complete(EnvironmentNodeCSharedPtr node) {
            m_not_visited.erase(node);
            m_visited.erase(node);
            m_done.insert(node);
        }
        
        EnvironmentNodeCSharedPtr next_not_visited() { return *m_not_visited.begin(); }
        
        bool not_visited(EnvironmentNodeCSharedPtr node) { return m_not_visited.contains(node); }
        bool visited(EnvironmentNodeCSharedPtr node) { return m_visited.contains(node); }
        bool completed(EnvironmentNodeCSharedPtr node) { return m_done.contains(node); }
        
        bool all_done() { return m_not_visited.empty() && m_visited.empty(); }
    };
    
    // MARK: Contexts
    
    struct GlobalContext {
        std::map<NumberReference, Dual> number_references;
//        std::map<const FunctionReference, std::function<double(std::vector<double>)>> function_references;
        
        std::shared_ptr<VisitMarker> visit_marker;
        
        GlobalContext(std::set<EnvironmentNodeCSharedPtr> nodes) : visit_marker(std::make_shared<VisitMarker>(nodes)) {};
    };
    
    typedef boost::variant<std::shared_ptr<GlobalContext>> var_GlobalContext;
    
    // MARK: Constructors
    
    Calculator() = delete;
    
    Calculator(Environment::SharedPtr env) : m_env(env) {}
    
    // MARK: Public getters
    
    const Environment::SharedPtr environment() const { return m_env; }
    
    // MARK: Evaluation
    
    virtual result_type operator()(const ExpressionNode& node, const std::shared_ptr<GlobalContext> context) const = 0;
    
    std::map<EnvironmentNodeCSharedPtr, result_type> eval_all_in_environment() const {
        std::map<Math::EnvironmentNodeCSharedPtr, result_type> result;
        
        const std::shared_ptr<GlobalContext> global_context = std::make_shared<GlobalContext>(m_env->nodes());
        
        while (!global_context->visit_marker->all_done()) {
            Math::EnvironmentNodeCSharedPtr node = global_context->visit_marker->next_not_visited();
            result.insert(std::make_pair(node, eval(node, global_context)));
        }
        
        return result;
    }
    
protected:
    
    // MARK: Member variables
    
    Environment::SharedPtr m_env;
    
    // MARK: Specific evaluation implementation
    
    result_type eval(EnvironmentNodeCSharedPtr node, const std::shared_ptr<GlobalContext> context) const {
        if (context->visit_marker->visited(node)) {
            throw ReferenceError("cyclical reference detected");
        }
        context->visit_marker->mark(node);
        result_type result = boost::apply_visitor(*this, *node, var_GlobalContext(context));
        context->visit_marker->complete(node);
        return result;
    }
    
};

} /* namespace Math */

#endif /* Calculator_hpp */
