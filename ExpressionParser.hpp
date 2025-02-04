#pragma once

#include "Tokenizer.hpp"
#include <string>
#include <vector>

class ExpressionParser 
{
public:
    static bool validateExpression(const std::string& expression);
    static std::string toPostfix(const std::vector<Token>& tokens);
    static std::string simplify(const std::string& expression);
    static std::string extractCommonVariable(const std::string& expr1, const std::string& expr2);
    static bool containsSameVariable(const std::string& expr1, const std::string& expr2);
    
private:
    static int getPrecedence(const std::string& op);
};