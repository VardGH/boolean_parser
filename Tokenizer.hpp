#pragma once

#include <vector>
#include <string>

enum class TokenType
{
    VARIABLE,
    OPERATOR,
    PARENTHESIS
};

struct Token
{
    TokenType type;
    std::string value;
};

inline std::string to_string(TokenType type)
{
    switch (type)
    {
    case TokenType::VARIABLE:
        return "VARIABLE";
    case TokenType::OPERATOR:
        return "OPERATOR";
    case TokenType::PARENTHESIS:
        return "PARENTHESIS";
    default:
        return "UNKNOWN";
    }
}

class Tokenizer
{
public:
    static std::vector<Token> tokenize(const std::string& expression);
};