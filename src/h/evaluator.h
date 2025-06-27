#ifndef EVALUATOR_H
#define EVALUATOR_H

#include <string>
#include <unordered_map>
#include "variable.h"

bool evaluateCondition(const std::unordered_map<std::string, Variable>& vars,
                      const std::string& lhs,
                      const std::string& op,
                      const std::string& rhsRaw);
std::string evalExpression(const std::string& expr);

#endif