#ifndef WGP___TOKEN_H
#define WGP___TOKEN_H

#include <iostream>
#include <vector>

enum _TokenType {
    KEYWORD,
    NUMBER,
    SEMI_COLON,
    STRING
};

typedef struct TOKEN {
    _TokenType type;
    std::string value;
} token;
std::vector<std::vector<token>> thds;

#endif
