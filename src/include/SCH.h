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

int chk_print (std::vector<token> *list) {
    if ( list->size() != 3 ) no_right_number_arguments();
    if ( list->at(1).type == STRING ) return 1;
    if ( list->at(1).type == ID ) return 0;

    wrong_type_argument();
    return -1;
}

int chk_int_declaration (std::vector<token> *list) {
    if ( list->size() <= 4 ) no_right_number_arguments();
    if ( list->at(3).type == NUMBER ) return 1;

    wrong_type_argument();
    return -1;
}



#endif
