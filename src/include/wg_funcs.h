#ifndef WG___WG_FUNCS_H
#define WG___WG_FUNCS_H

#include "token.h"
#include "assembly-generator.h"
#include "assembly-templates.h"
#include "err-report.h"
#include <cmath>

int to_int (std::string src) {
    return std::atoi(src.c_str());
}

int WG_arith (std::vector<token> *op) {
    int value = to_int(op->at(2).value.c_str());

    for (size_t i = 3; i < op->size() - 1; i+=2) {
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

void type_arith_call (std::vector<token> *list, temp* _temp) {
    /* There are two types of arithmetic call:
     * 1. When there are only numbers and there are not variables.  :: ARITH(3 sub 5 add 1)
     * 2. When there are variables and numbers.                     :: ARITH($x$ add $r$ mul 4)
     *
     * Solutions:
     * 1. The formula will be solved by C++      (c)
     * 2. The formula will be solved by Assembly (a) */
    char arith_type = 'c';
    size_t idxArithToken = 0;
    size_t idxRparnToken = 0;

    for (size_t i = 0; i < list->size(); ++i) {
        if ( list->at(i).type == WGPP_FUNC && list->at(i).value == "ARITH" )
            idxArithToken = i;
        if ( list->at(i).type == RIGHT_P )
            idxRparnToken = i;
        if ( idxRparnToken && idxArithToken )
            break;
    }

    std::vector<token> op = { list->begin() + idxArithToken, list->begin() + idxArithToken + idxRparnToken };
    for (size_t i = 2; i < op.size() - 1; ++i) {
        if ( !(i % 2) && ( op.at(i).type != NUMBER && op.at(i).type != ID ) )
            token_expected("NUMBER OR INTEGER VARIABLE");

        if ( (i % 2) && op.at(i).type != MATH_OPERATOR )
            token_expected("MATH OPERATOR");

        if ( op.at(i).type == ID ) {
            arith_type = 'a';
            break;
        }
    }

    if ( arith_type == 'c' ) {
        int result = WG_arith(&op);
        _wg_write_sys_exit_by_math_typeC(_temp, result);
    }
    else {
        _wg_write_sys_exit_by_math_typeA(_temp, &op);
    }
}

#endif







