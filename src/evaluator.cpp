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
        long long l = safeStoll(left.value);
        long long r = safeStoll(right.value);
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

long long safeStoll(const std::string& s) {
    try {
        return std::stoll(s);
    } catch (...) {
        throw std::runtime_error("Invalid integer: " + s);
    }
}

std::string evalExpression(const std::string& expr) {
    std::smatch match;
    std::regex mathRegex(R"(^(\d+)\s*([\+\-\*/%\^])\s*(\d+)$)");
    if (std::regex_match(expr, match, mathRegex)) {
        long long left = safeStoll(match[1]);
        char op = match[2].str()[0];
        long long right = safeStoll(match[3]);

        long long result = 0;
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