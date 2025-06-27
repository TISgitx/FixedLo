#ifndef UTILS_H
#define UTILS_H

#include <string>

std::string trim(const std::string& str);
bool isStringLiteral(const std::string& value);
std::string stripQuotes(const std::string& s);

#endif