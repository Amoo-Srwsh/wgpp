#ifndef WG___WG_FUNCS_H
#define WG___WG_FUNCS_H

#include "token.h"
#include <cmath>

int to_int (std::string src) {
    return std::atoi(src.c_str());
}

int WG_arith (std::vector<token> *op) {
    // op vector: int  $name$  =  ARITH  (  4  add  5  )  ;
    // op indexs:  0      1    2    3    4  5   6   7  8  9 
    // ( 4 mod 4 mod 5 mul 5 )
    int value = to_int(op->at(5).value.c_str());

    for (size_t i = 6; i < op->size() - 2; i+=2) {
        if ( op->at(i).value == "add" ) value += to_int(op->at(i + 1).value);
        if ( op->at(i).value == "sub" ) value -= to_int(op->at(i + 1).value);
        if ( op->at(i).value == "mul" ) value *= to_int(op->at(i + 1).value);
        if ( op->at(i).value == "div" ) value /= to_int(op->at(i + 1).value);
        if ( op->at(i).value == "mod" ) value %= to_int(op->at(i + 1).value);
        if ( op->at(i).value == "pot" ) {
            value = pow(value, to_int(op->at(i + 1).value));
        }
    }

    return value;
}

#endif
