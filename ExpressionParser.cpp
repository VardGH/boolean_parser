#include "ExpressionParser.hpp"
#include "Exceptions.hpp"
#include "Tokenizer.hpp"
#include <stack>
#include <sstream>
#include <unordered_set>
#include <algorithm>
#include <iostream>

bool ExpressionParser::validateExpression(const std::string& expression)
{
    int balance = 0;
    bool lastWasOperator = true;
    bool lastWasOperand = false;

    size_t length = expression.length();
    for (size_t i = 0; i < length; ++i) {
        char c = expression[i];
        if (std::isspace(c)) continue;

        if (std::isalpha(c)) {  
            if (lastWasOperand) return false; // invalid "a b"
            lastWasOperand = true;
            lastWasOperator = false;
        } 
        else if (c == '(') {
            if (lastWasOperand) return false;  // invalid: "a("
            ++balance;
            lastWasOperator = true;
            lastWasOperand = false;
        } 
        else if (c == ')') {
            if (lastWasOperator) return false; // invalid: "()" or "&&)"
            --balance;
            if (balance < 0) return false;
            lastWasOperand = true;
        } 
        else if (c == '!') {
            lastWasOperator = true;
            lastWasOperand = false;
        } 
        else if (i + 1 < length && (expression.substr(i, 2) == "&&" || expression.substr(i, 2) == "||")) {
            if (lastWasOperator) return false; // invalid: "&& a" or "|| a"
            lastWasOperator = true;
            lastWasOperand = false;
            ++i;  // skip second character of "&&" or "||"
        } 
        else {
            return false; // invalid character
        }
    }

    return balance == 0 && !lastWasOperator;
}

int ExpressionParser::getPrecedence(const std::string& op)
{
    if (op == "!") return 3;
    if (op == "&&") return 2;
    if (op == "||") return 1;
    return 0;
}

std::string ExpressionParser::toPostfix(const std::vector<Token>& tokens) 
{
    std::stack<std::string> opStack;
    std::string postfix;

    for (const auto& token : tokens) {
        if (token.type == TokenType::VARIABLE) {
            postfix += token.value + " ";
        } else if (token.type == TokenType::OPERATOR) {
            while (!opStack.empty() && opStack.top() != "(" && getPrecedence(opStack.top()) >= getPrecedence(token.value)) {
                postfix += opStack.top() + " ";
                opStack.pop();
            }
            opStack.push(token.value);
        } else if (token.value == "(") {
            opStack.push(token.value);
        } else if (token.value == ")") {
            while (!opStack.empty() && opStack.top() != "(") {
                postfix += opStack.top() + " ";
                opStack.pop();
            }
            opStack.pop(); // remove "("
        }
    }

    while (!opStack.empty()) {
        postfix += opStack.top() + " ";
        opStack.pop();
    }

    return postfix;
}

bool isOperator(const std::string& token) 
{
    return token == "!" || token == "&&" || token == "||";
}
 
std::string ExpressionParser::simplify(const std::string& expression) {
    std::vector<Token> tokens = Tokenizer::tokenize(expression);
    std::string postfix = toPostfix(tokens);
    std::stack<std::string> opStack;
    std::istringstream postfixStream(postfix);
    std::string token;

    while (postfixStream >> token) {
        if (std::isalpha(token[0])) {
            opStack.push(token);
            continue;
        }

        if (token == "!") {
            if (opStack.empty()) {
                throw InsufficientOperandsException("Invalid Boolean expression: insufficient operands.");
            }
            std::string operand = opStack.top();
            opStack.pop();
            
            if (operand[0] == '!') {
                opStack.push(operand.substr(1));
            } else {
                opStack.push("!" + operand);
            }
            continue;
        }

        if (opStack.size() < 2) {
            throw InsufficientOperandsException("Invalid Boolean expression: insufficient operands.");
        }

        std::string right = opStack.top(); 
        opStack.pop();
        std::string left = opStack.top(); 
        opStack.pop();

        if (token == "||") {
            // Check for absorption: a || (a && b) = a
            if (right.find(left) != std::string::npos || left.find(right) != std::string::npos) {
                opStack.push(left);
            }
            // Check for operands containing the same variable
            else if (containsSameVariable(left, right)) {
                opStack.push(extractCommonVariable(left, right));
            } 
            else {
                opStack.push(left + " || " + right);
            }
        }
        else if (token == "&&") {
            // Check for common variables: a && b && a = a && b
            if (right.find(left) != std::string::npos || left.find(right) != std::string::npos) {
                opStack.push(std::min(left, right));
            }
            else {
                opStack.push(left + " && " + right);
            }
        }
    }

    std::string result;
    while (!opStack.empty()) {
        result = opStack.top() + " " + result;
        opStack.pop();
    }

    if (!result.empty() && result.back() == ' ') {
        result.pop_back();
    }

    return result;
}

bool ExpressionParser::containsSameVariable(const std::string& expr1, const std::string& expr2) {
    std::unordered_set<char> vars1, vars2;
    
    for (char c : expr1) {
        if (std::isalpha(c)) vars1.insert(c);
    }
    
    for (char c : expr2) {
        if (std::isalpha(c)) vars2.insert(c);
    }
    
    for (char var : vars1) {
        if (vars2.find(var) != vars2.end()) return true;
    }
    return false;
}

std::string ExpressionParser::extractCommonVariable(const std::string& expr1, const std::string& expr2) {
    std::unordered_set<char> vars1;
    for (char c : expr1) {
        if (std::isalpha(c)) vars1.insert(c);
    }
    
    for (char c : expr2) {
        if (std::isalpha(c) && vars1.find(c) != vars1.end()) {
            return std::string(1, c);
        }
    }
    return expr1;  // fallback
}