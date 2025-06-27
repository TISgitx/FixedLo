#ifndef FUNCTION_H
#define FUNCTION_H

#include <string>
#include <vector>

struct FunctionDef {
    std::string returnType;
    std::vector<std::pair<std::string, std::string>> params;
    std::vector<std::string> body;
};

#endif