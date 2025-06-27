#ifndef EXECUTOR_H
#define EXECUTOR_H

#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include "variable.h"
#include "function.h"

std::string executeFunction(const FunctionDef& func,
                           const std::vector<std::string>& args,
                           const std::map<std::string, FunctionDef>& functions,
                           const std::unordered_map<std::string, Variable>& globalVars);

#endif