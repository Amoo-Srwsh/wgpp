#ifndef WG___TOKEN_H
#define WG___TOKEN_H

#include <iostream>
#include <vector>

enum TokenType {
    THEAD,
    EXIT_FUNCTION,
    NUMBER,
    SEMI_COLON,
    PRINT_FUNCTION,
    STRING
};

typedef struct TOKEN {
    TokenType type;
    std::string value;
    TOKEN* children;
} token;
std::vector<std::vector<token>> Thead;

#endif
