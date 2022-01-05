#ifndef WG___SHC_H
#define WG___SHC_H

#include "err-report.h"
#include "token.h"

int chk_exit_by_number (std::vector<token> *list) {
    if ( list->size() != 3 ) {
        no_right_number_arguments();
        exit(1);
    }

    // TODO: Make no right argument error here
    if ( list->at(1).type == NUMBER )
        return 1;
    else
        exit(90);
}

int chk_print (std::vector<token> *list) {
    if ( list->size() != 3 ) {
        no_right_number_arguments();
        exit(1);
    }

    // TODO: Make no right argument error here
    if ( list->at(1).type == STRING )
        return 1;
    else
        exit(90);
}


#endif
