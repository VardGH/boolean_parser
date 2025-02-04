#include "../ExpressionParser.hpp"
#include <iostream>
#include <string>

#define ANSI_GREEN "\033[32m"
#define ANSI_RED "\033[31m"
#define ANSI_RESET "\033[0m"

#define TEST(bool_expr, ID)\
    if ((bool_expr)) {\
        std::cout << ANSI_GREEN << "PASSED" << ANSI_RESET;\
    } else {\
        std::cout << ANSI_RED << "FAILED" << ANSI_RESET;\
    }\
    std::cout << ' ' << ID << '\n';


int main()
{
    TEST(ExpressionParser::simplify("a || (a&&b)") == "a", "remove duplicates with brekets");
    TEST(ExpressionParser::simplify("a || a && b") == "a", "remove duplicates without brekets");
    TEST(ExpressionParser::simplify("a && b && a") == "a", "remove from and duplicates");
    TEST(ExpressionParser::simplify("a && b || a") == "a && b", "remove from and duplicates");
    TEST(ExpressionParser::simplify("a || b || a ") == "a || b", "remove unnacessary or duplicates");
    TEST(ExpressionParser::simplify("b &&(a || (a&&b))") == "b && a", "multiple brackets");
    TEST(ExpressionParser::simplify(" a && b || c && d") == "a && b || c && d", "remove from and duplicates");
    TEST(ExpressionParser::simplify("a && (b || c)") == "a && b || c", "opening the brekets");

    return 0;
}