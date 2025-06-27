#include "h/utils.h"

std::string trim(const std::string& str) {
    size_t first = str.find_first_not_of(" \t");
    if (first == std::string::npos) return "";
    size_t last = str.find_last_not_of(" \t");
    return str.substr(first, (last - first + 1));
}

bool isStringLiteral(const std::string& value) {
    return value.size() >= 2 && value.front() == '"' && value.back() == '"';
}

std::string stripQuotes(const std::string& s) {
    if (isStringLiteral(s)) return s.substr(1, s.size() - 2);
    return s;
}