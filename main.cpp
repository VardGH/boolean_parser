#include "ExpressionParser.hpp"
#include <iostream>
#include <string>

int main()
{
    std::string inputExpression;
    
    std::cout << "Enter a Boolean expression: ";
    std::getline(std::cin, inputExpression);
    // a || (a&&b)       -> a
    // a || a && b       -> a 
    // a && b && a       -> a
    // a && b || a       -> a && b
    // a || b || a       -> a || b
    // b &&(a || (a&&b)) -> b && a
    // a && b || c && d  -> a && b || c && d
    // a && (b || c)     -> a && b || c
    try {
        ExpressionParser parser;

        // validate expr
        if (!parser.validateExpression(inputExpression)) {
            std::cerr << "Error: Invalid Boolean expression syntax.\n";
            return 1;
        }

        // simplify expr
        std::string simplifiedExpression = ExpressionParser::simplify(inputExpression);

        std::cout << "Simplified Expression: " << simplifiedExpression << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}