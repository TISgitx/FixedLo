// main.cpp 
#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <string>
#include <regex>
#include <vector>
#include <map>
#include "src/h/variable.h"
#include "src/h/function.h"
#include "src/h/utils.h"
#include "src/h/evaluator.h"
#include "src/h/executor.h"

std::unordered_map<std::string, Variable> variables;

int main(int argc, char* argv[]) {
    if (argc < 2) { std::cerr << "Usage: lomake <file.lo>\n"; return 1; }

    std::ifstream file(argv[1]);
    if (!file) {
        std::cerr << "Failed to open file: " << argv[1] << "\n";
        return 1;
    }

    std::map<std::string, FunctionDef> functions;
    std::string line;
    std::vector<std::string> lines;
    while (std::getline(file, line)) lines.push_back(trim(line));

    bool inIf = false, ifMatched = false, skip = false;
    bool inFunction = false;
    FunctionDef currentFunction;
    std::string currentFunctionName;

    std::regex locRegex(R"(^loc\s+(\w+)\s*=\s*(int|str)\(([^)]*)\)\s*!$)");
    std::regex assignRegex(R"(^(\w+)\s*=\s*([^!]+)\!$)");
    std::regex printRegex(R"(^print--\s*(\w+|\"[^\"]*\"|f-(\w+)\(([^)]*)\))!$)");
    std::regex ifRegex(R"(if-\s*(\w+)\s*(>>|<<|===)\s*(\w+)\s*the)");
    std::regex elifRegex(R"(elif-\s*(\w+)\s*(>>|<<|===)\s*(\w+)\s*the)");
    std::regex funRegex(R"(^funS\s+(\w)\s+(\w+)\(([^)]*)\):\s*\{$)");
    std::regex returnRegex(R"(^return\s+(.*)!$)");
    std::regex inputRegex(R"(^(\w+)\s*=\s*input--\s*(i|str)-\s*\"([^\"]*)\"!$)");

    for (size_t i = 0; i < lines.size(); ++i) {
        const std::string& ln = lines[i];
        std::smatch match;
        if (ln.empty()) continue;

        if (inFunction) {
            if (ln == "}") {
                functions[currentFunctionName] = currentFunction;
                inFunction = false;
            } else {
                currentFunction.body.push_back(ln);
            }
            continue;
        }

        if (std::regex_match(ln, match, funRegex)) {
            inFunction = true;
            currentFunction.returnType = match[1];
            currentFunctionName = match[2];
            currentFunction.body.clear();
            currentFunction.params.clear();

            std::string paramStr = match[3];
            std::stringstream ss(paramStr);
            std::string param;
            while (std::getline(ss, param, ',')) {
                size_t colon = param.find(':');
                if (colon != std::string::npos) {
                    std::string type = trim(param.substr(0, colon));
                    std::string name = trim(param.substr(colon + 1));
                    currentFunction.params.emplace_back(type, name);
                }
            }
            continue;
        }

        if (std::regex_match(ln, match, locRegex)) {
            std::string name = match[1], type = match[2], val = match[3];
            if (type == "str" && val.front() == '"' && val.back() == '"')
                val = val.substr(1, val.length() - 2);
            else if (type == "int")
                val = evalExpression(val);
            variables[name] = { type, val };

        } else if (std::regex_match(ln, match, inputRegex)) {
            std::string name = match[1], type = match[2], prompt = match[3];
            std::cout << prompt;
            std::string input;
            std::getline(std::cin, input);
            if (type == "i") {
                try {
                    std::stoi(input);
                    variables[name] = { "int", input };
                } catch (...) {
                    std::cerr << "Invalid input for int: " << input << std::endl;
                    return 1;
                }
            } else if (type == "str") {
                variables[name] = { "str", input };
            }

        } else if (std::regex_match(ln, match, assignRegex)) {
            std::string name = match[1];
            std::string val = trim(match[2]);

            if (!variables.count(name)) {
                std::cerr << "Undefined variable: " << name << std::endl;
                return 1;
            }

            auto& var = variables[name];
            if (var.type == "int")
                var.value = evalExpression(val);
            else if (var.type == "str") {
                if (val.front() == '"' && val.back() == '"')
                    val = val.substr(1, val.length() - 2);
                var.value = val;
            }

        } else if (std::regex_match(ln, match, ifRegex)) {
            inIf = true;
            ifMatched = evaluateCondition(variables, match[1], match[2], match[3]);
            skip = !ifMatched;

        } else if (std::regex_match(ln, match, elifRegex)) {
            if (inIf && !ifMatched) {
                ifMatched = evaluateCondition(variables, match[1], match[2], match[3]);
                skip = !ifMatched;
            } else {
                skip = true;
            }

        } else if (ln == "end--") {
            inIf = false;
            skip = false;
            ifMatched = false;

        } else if (!skip) {
            if (std::regex_match(ln, match, printRegex)) {
                if (match[2].matched) {
                    std::string fname = match[2];
                    std::string argsStr = match[3];
                    std::vector<std::string> args;
                    std::stringstream ss(argsStr);
                    std::string arg;
                    while (std::getline(ss, arg, ',')) args.push_back(trim(arg));
                    if (functions.count(fname)) {
                        std::string result = executeFunction(functions.at(fname), args, functions, variables);
                        std::cout << result << std::endl;
                    } else {
                        std::cerr << "Undefined function: " << fname << std::endl;
                        return 1;
                    }
                } else {
                    std::string val = match[1];
                    if (val.front() == '"') {
                        std::cout << val.substr(1, val.length() - 2) << std::endl;
                    } else if (variables.count(val)) {
                        std::cout << variables[val].value << std::endl;
                    } else {
                        std::cerr << "Undefined variable: " << val << std::endl;
                    }
                }
            } else {
                std::cerr << "Syntax error at line " << i + 1 << ": " << ln << std::endl;
                return 1;
            }
        }
    }

    return 0;
}