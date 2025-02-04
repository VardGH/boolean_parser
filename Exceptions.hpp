#pragma once

#include <exception>
#include <string>

class InsufficientOperandsException : public std::exception
{
public:
    InsufficientOperandsException(std::string&& message)
        : message_(message)
    {}

    const char* what() const noexcept override
    {
        return message_.c_str();
    }

private:
    std::string message_;
};

class MismatchedParenthesesException : public std::exception
{
public:
    MismatchedParenthesesException(std::string&& message)
        : message_(message)
    {}

    const char* what() const noexcept override
    {
        return message_.c_str();
    }

private:
    std::string message_;
};

class InvalidCharacterException : public std::exception
{
public:
    InvalidCharacterException(std::string&& message)
        : message_(message)
    {}

    const char* what() const noexcept override
    {
        return message_.c_str();
    }

private:
    std::string message_;
};