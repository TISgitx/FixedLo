#include "h/executor.h"
#include "h/evaluator.h"
#include "h/utils.h"
#include <regex>

std::string executeFunction(const FunctionDef& func,
                           const std::vector<std::string>& args,
                           const std::map<std::string, FunctionDef>& functions,
                           const std::unordered_map<std::string, Variable>& globalVars) {
    std::unordered_map<std::string, Variable> localVars;
    for (size_t i = 0; i < func.params.size(); ++i) {
        std::string value = args[i];
        if (value.front() != '"' && localVars.count(value) == 0 && globalVars.count(value)) {
            value = globalVars.at(value).value;
        }
        localVars[func.params[i].second] = { func.params[i].first, value };
    }

    for (const auto& line : func.body) {
        std::smatch match;
        std::regex locRegex(R"(^loc\s+(\w+)\s*=\s*(int|str)\(([^)]*)\)\s*!$)");
        std::regex returnRegex(R"(^return\s+(.*)!$)");

        if (std::regex_match(line, match, locRegex)) {
            std::string name = match[1], type = match[2], val = match[3];
            if (type == "str" && val.front() == '"' && val.back() == '"')
                val = val.substr(1, val.size() - 2);
            else if (type == "int")
                val = evalExpression(val);
            localVars[name] = {type, val};
        } else if (std::regex_match(line, match, returnRegex)) {
            std::string ret = match[1];
            for (const auto& [name, var] : localVars) {
                size_t pos;
                while ((pos = ret.find(name)) != std::string::npos) {
                    ret.replace(pos, name.length(), var.value);
                }
            }
            return evalExpression(ret);
        }
    }

    return "";
}