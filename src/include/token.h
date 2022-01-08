#ifndef WGP___TOKEN_H
#define WGP___TOKEN_H

#include <iostream>
#include <vector>

enum _TokenType {
    KEYWORD,
    NUMBER,
    SEMI_COLON,
    STRING,
    VARIABLE, // could be a integer, string or pointer
    ID,
    EQUALS_S,
    WGPP_FUNC, // functions that belong to wgpp such as: ARITH to make arithmetic
    LEFT_P,
    RIGHT_P,
    MATH_OPERATOR,
    ANY_TYPE_VAR
};

typedef struct TOKEN {
    _TokenType type;
    std::string value;
} token;
std::vector<std::vector<token>> thds;

#endif
