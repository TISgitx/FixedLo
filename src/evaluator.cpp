#include "h/evaluator.h"
#include "h/utils.h"
#include <regex>
#include <cmath>

bool evaluateCondition(const std::unordered_map<std::string, Variable>& vars,
                      const std::string& lhs,
                      const std::string& op,
                      const std::string& rhsRaw) {
    if (!vars.count(lhs)) return false;
    const auto& left = vars.at(lhs);

    std::string rhsStripped = stripQuotes(rhsRaw);
    Variable right;

    if (vars.count(rhsRaw)) {
        right = vars.at(rhsRaw);
    } else {
        if (left.type == "str") right = Variable{"str", rhsStripped};
        else if (left.type == "int") right = Variable{"int", rhsStripped};
        else return false;
    }

    if (left.type != right.type) return false;

    if (left.type == "int") {
        int l = std::stoi(left.value);
        int r = std::stoi(right.value);
        if (op == ">>") return l > r;
        if (op == "<<") return l < r;
        if (op == "===") return l == r;
    } else if (left.type == "str") {
        if (op == "===") return left.value == right.value;
        if (op == ">>") return left.value > right.value;
        if (op == "<<") return left.value < right.value;
    }

    return false;
}

std::string evalExpression(const std::string& expr) {
    std::smatch match;
    std::regex mathRegex(R"(^(\d+)\s*([\+\-\*/%\^])\s*(\d+)$)");
    if (std::regex_match(expr, match, mathRegex)) {
        int left = std::stoi(match[1]);
        char op = match[2].str()[0];
        int right = std::stoi(match[3]);

        int result = 0;
        switch (op) {
            case '+': result = left + right; break;
            case '-': result = left - right; break;
            case '*': result = left * right; break;
            case '/': result = right != 0 ? left / right : 0; break;
            case '%': result = right != 0 ? left % right : 0; break;
            case '^': result = std::pow(left, right); break;
        }
        return std::to_string(result);
    }
    return expr;
}