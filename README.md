# Tokenizer Project

## Problem Statement

This project implements a tokenizer that parses a given expression string and converts it into a list of tokens. The tokenizer supports:
- Single-character variables [a, z]
- Multi-character operators like "&&" and "||"
- Single-character operators like "!"
- Parentheses "(" and ")"
- Throws an error for any invalid characters in the expression

## Run Requirements

To run this project, you need the following:

1. **C++ Compiler**: Ensure you have a C++ compiler installed on your system. For example, `g++` on macOS or Linux, or Visual Studio on Windows.
2. **C++ Standard Library**: The project uses standard C++ libraries, so no additional libraries are required.

## How to Compile and Run

1. **Clone the Repository**:
    ```sh
    git clone <repository-url>
    cd <repository-directory>
    ```

2. **Compile the Code**:
    ```sh
    make
    ```

3. **Run the Executable**:
    ```sh
    bin/simplifier
    ```

4. **Complied Unit tests**:
    ```sh
    make tests
    ```

5. **Run Unit tests**:
    ```sh
    bin/utests
    ```