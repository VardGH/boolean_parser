#include "Tokenizer.hpp"
#include "Exceptions.hpp"
#include <cctype>
#include <iostream>

std::vector<Token> Tokenizer::tokenize(const std::string& expression)
{
    std::vector<Token> tokens;
    size_t i = 0;

    while (i < expression.length()) {
        if (std::isspace(expression[i])) {
            ++i;
            continue;
        }

        if (std::isalpha(expression[i])) { 
            tokens.push_back({TokenType::VARIABLE, std::string(1, expression[i])});
            ++i;
        }
        // Check for multi-character operators "&&", "||"
        else if (i + 1 < expression.length() && (expression.substr(i, 2) == "&&" || expression.substr(i, 2) == "||")) {
            tokens.push_back({TokenType::OPERATOR, expression.substr(i, 2)});
            i += 2;
        }
        else if (expression[i] == '!') {
            tokens.push_back({TokenType::OPERATOR, "!"});
            ++i;
        }
        else if (expression[i] == '(' || expression[i] == ')') {
            tokens.push_back({TokenType::PARENTHESIS, std::string(1, expression[i])});
            ++i;
        }
        else {
            throw InvalidCharacterException("Invalid character in expression: " + std::string(1, expression[i]));
        }
    }

    return tokens;
}