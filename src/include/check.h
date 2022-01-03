#ifndef WG___CHECK_H
#define WG___CHECK_H

#include "token.h"
#include "error-table.h"

bool exit_function_by_number (std::vector<token> *head) {
    if ( head->size() != 3 ) {
        _err_arguments();
    }

    if ( head->at(1).type != NUMBER && head->at(1).type != VAR_NAME ) {
        _err_different_type();
    }

    if ( head->at(1).type == NUMBER ){
        return true;
    }
    return false;
}

bool print_function_by_str (std::vector<token> *head) {
    if ( head->size() != 3 ) {
        _err_arguments();
    }

    // could be a variable too
    if ( head->at(1).type != STRING && head->at(1).type != VAR_NAME ) {
        _err_different_type();
    }

    if ( head->at(1).type == STRING ){
        return true;
    }
    return false;
}

#endif
