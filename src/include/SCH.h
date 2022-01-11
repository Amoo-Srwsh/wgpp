#ifndef WG___SHC_H
#define WG___SHC_H

#include "err-report.h"
#include "token.h"
#include "variables.h"

char chk_exit_by_number (std::vector<token> *list) {
    // done
    if ( list->size() <= 2 )            no_right_number_arguments();
    if ( list->at(1).type == NUMBER )   return 'n';
    if ( list->at(1).type == ID )       return 'v';
    if ( list->at(1).type == WGPP_FUNC && list->at(1).value == "ARITH" )
        return 'm';

    wrong_type_argument();
    return 'N';
}

char chk_wout (std::vector<token> *list) {
    // done
    if ( list->size() <= 2 )           no_right_number_arguments();
    if ( list->at(1).type == STRING )  return 's';
    if ( list->at(1).type == ID )      return 'v';
    if ( list->at(1).type == WGPP_FUNC && list->at(1).value == "ARITH" )
        return 'm';

    wrong_type_argument();
    return 'N';
}

char chk_int_declaration (std::vector<token> *list) {
    // done
    var *doesnt_exit = get_variable_without_throw_error(list->at(1).value, NUMBER);
    if ( doesnt_exit != nullptr )
        overwrite_variable(list->at(1).value);

    if ( list->size() <= 4 )           no_right_number_arguments();
    if ( list->at(3).type == NUMBER )  return 'n';
    if ( list->at(3).type == ID )      return 'v';
    if ( list->at(3).type == WGPP_FUNC && list->at(3).value == "ARITH" )
        return 'm';

    return 'N';
}

void chk_printf (std::vector<token> *list) {
    // done
    if ( list->size() != 3 )           no_right_number_arguments();
    if ( list->at(1).type != STRING )  token_expected("STRING");
}

char chk_chg (std::vector<token> *list) {
    // chg $x$ new;
    if ( list->size() <= 3 )           no_right_number_arguments();
    if ( list->at(2).type == NUMBER )  return 'n';
    if ( list->at(2).type == ID )      return 'v';
    if ( list->at(2).type == WGPP_FUNC && list->at(2).value == "ARITH" )
        return 'm';

    wrong_type_argument();
    return 'N';
}

#endif
