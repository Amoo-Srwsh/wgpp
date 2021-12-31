#ifndef WG___CHECK_H
#define WG___CHECK_H

#include "token.h"
#include "error-table.h"

bool exit_function_by_number (std::vector<token> *head) {
    if ( head->size() != 3 ) {
        _err_many_arguments();
    }

    // could be a integer variable too
    if ( head->at(1).type != NUMBER ) {
        _err_different_type();
    }

    if ( head->at(1).type == NUMBER ){
        return true;
    }
    return false;
}

#endif
