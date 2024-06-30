//
//  Evaluator.hpp
//  Diffintegrator
//
//  Created by Ivan on 4/3/24.
//

#ifndef Evaluator_hpp
#define Evaluator_hpp

#include <functional>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <boost/variant/static_visitor.hpp>

#include "Calculator.hpp"
#include "Dual.hpp"
#include "Environment.hpp"
#include "EnvironmentNode.hpp"

namespace Math {

class Evaluator : public Calculator<Dual> {
public:
    
    Evaluator(Environment::SharedPtr env) : Calculator<Dual>(env) {};
    
    virtual Dual operator()(const ExpressionNode& node, const std::shared_ptr<GlobalContext> context) const override;

};

} /* namespace Calc */

#endif /* Evaluator_hpp */
