#ifndef WG___SHC_H
#define WG___SHC_H

#include "err-report.h"
#include "token.h"
#include "variables.h"

char chk_exit_by_number (std::vector<token> *list) {
    // done
    if ( list->size() <= 2 )
        no_right_number_arguments();
    if ( list->at(1).type == NUMBER ) 
        return 'n';
    if ( list->at(1).type == ID )
        return 'v';
    if ( list->at(1).type == WGPP_FUNC && list->at(1).value == "ARITH" )
        return 'm';

    wrong_type_argument();
    return 'N';
}

char chk_wout (std::vector<token> *list) {
    if ( list->size() != 3 )           no_right_number_arguments();
    if ( list->at(1).type == STRING )  return 's';
    if ( list->at(1).type == ID )      return 'v';

    // TODO: wout a mathematical operation
    wrong_type_argument();
    return 'N';
}

char chk_int_declaration (std::vector<token> *list) {
    // TODO: check overwrite
    if ( list->size() <= 4 )           no_right_number_arguments();
    if ( list->at(3).type == NUMBER )  return 'n';
    if ( list->at(3).type == ID )      return 'v';

    // TODO: make int with arithmetic
    return 'N';
}

void chk_printf (std::vector<token> *list) {
    // done
    if ( list->size() != 3 )           no_right_number_arguments();
    if ( list->at(1).type != STRING )  token_expected("STRING");
}


#endif

/*
void _check_ARITH_function (std::vector<token> *list, size_t from, int *type_) {
    for (size_t i = from; i < list->size() - 2; ++i) {
        if ( (i % 2) != 0 && (list->at(i).type != NUMBER && list->at(i).type != ID )) token_expected("NUMBER OR INTEGER VARIABLE");
        if ( !(i % 2) && list->at(i).type != NUMBER ) token_expected("MATH OPERATOR");

        if ( (i % 2) != 0 && list->at(i).type == ID ) *type_ = 2;
    }
}

int chk_int_declaration (std::vector<token> *list) {
    var* maybe_alredy_exists = get_variable_without_throw_error(list->at(1).value, NUMBER);
    if ( maybe_alredy_exists )
        overwrite_variable(list->at(1).value);

    if ( list->size() <= 4 ) no_right_number_arguments();
    if ( list->at(3).type == NUMBER ) return 1;
    if ( list->at(3).type == ID ) return 0;

    if ( list->at(3).type == WGPP_FUNC && list->at(3).value == "ARITH" ) {
        // int $x$ = arith();
        if ( list->at(4).type != LEFT_P ) token_expected("Left parenthesis");
        if ( list->at(list->size() - 2).type != RIGHT_P ) token_expected("Right parenthesis");
        int type_ = 3;
        _check_ARITH_function(list, 5, &type_);

        return type_;
    }

    wrong_type_argument();
    return -1;
}

void chk_printf (std::vector<token> *list) {
    if ( list->size() != 3 ) no_right_number_arguments();
    if ( list->at(1).type != STRING ) wrong_type_argument();
}

char chk_CHG (std::vector<token> *list) {
    if ( list->size() <= 3 ) no_right_number_arguments();
    if ( list->at(2).type == NUMBER ) return 'n';
    if ( list->at(2).type == ID ) return 'i';
    if ( list->at(2).type == WGPP_FUNC && list->at(2).value == "ARITH" ) {
        int _type = 0;
        _check_ARITH_function(list, 4, &_type);
        return 'm';
    }

    token_expected("ANOTHER VARIABLE WITH THE SAME TYPE OR NEW VALUE WITH THE SAME TYPE OF THE ORIGINAL VARIABLE");
    return '0';
}*/

