#ifndef WG___SHC_H
#define WG___SHC_H

#include "err-report.h"
#include "token.h"

int chk_exit_by_number (std::vector<token> *list) {
    if ( list->size() != 3 ) {
        no_right_number_arguments();
    }

    if ( list->at(1).type == NUMBER )
        return 1;
    if ( list->at(1).type == ID )
        return 0;

    wrong_type_argument();
    return -1;
}

int chk_wout (std::vector<token> *list) {
    if ( list->size() != 3 ) no_right_number_arguments();
    if ( list->at(1).type == STRING ) return 1;
    if ( list->at(1).type == ID ) return 0;

    wrong_type_argument();
    return -1;
}

int chk_int_declaration (std::vector<token> *list) {
    if ( list->size() <= 4 ) no_right_number_arguments();
    if ( list->at(3).type == NUMBER ) return 1;
    if ( list->at(3).type == ID ) return 0;

    if ( list->at(3).type == WGPP_FUNC && list->at(3).value == "ARITH" ) {
        if ( list->at(4).type != LEFT_P ) token_expected("Left parenthesis");
        if ( list->at(list->size() - 2).type != RIGHT_P ) token_expected("Right parenthesis");
        int type_ = 3;

        for (size_t i = 5; i < list->size() - 2; ++i) {
            if ( (i % 2) != 0 && (list->at(i).type != NUMBER && list->at(i).type != ID )) token_expected("NUMBER OR INTEGER VARIABLE");
            if ( !(i % 2) && list->at(i).type != MATH_OPERATOR ) token_expected("MATH OPERATOR");

            /* If one value is into a variable all proccess must be done by assembly.
             * If all numbers is not saved into variables the proccess is done by C++ and the value
             * of the operation is saved into the new variable */
            if ( (i % 2) != 0 && list->at(i).type == ID ) type_ = 2;
        }

        return type_;
    }

    wrong_type_argument();
    return -1;
}

void chk_printf (std::vector<token> *list) {
    if ( list->size() != 3 ) no_right_number_arguments();
    if ( list->at(1).type != STRING ) wrong_type_argument();
}

#endif
