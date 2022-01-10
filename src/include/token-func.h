#ifndef WG___TOKEN_FUNC_H
#define WG___TOKEN_FUNC_H

#include "token.h"
#include "assembly-templates.h"
#include "assembly-generator.h"
#include "SCH.h"
#include "variables.h"
#include "wg_funcs.h"


int insert_head () {
    thds.push_back( std::vector<token>() );
    return thds.size() - 1;
}

void push_token (int idx, _TokenType type, std::string value) {
    token* newtk = new (struct TOKEN);
    newtk->value = value;
    newtk->type = type;

    thds.at(idx).push_back(*newtk);
}

void print_tokens (std::vector<token> *current) {
    printf("TOKENS: <%s", current->at(0).value.c_str());
    for (size_t j = 1; j < current->size(); ++j) {
        printf(", %s", current->at(j).value.c_str());
    }
    printf(">\n");
}

void parser () {
    FILE *dataS = fopen("data.s", "w");
    FILE *codeS = fopen("code.s", "w");

    start_dataS(dataS);
    start_codeS(codeS);

    // Start point to linker
    mke_func_temp("main");
    size_t currnt_func = get_currnt_tmp();

    for (size_t i = 0; i < thds.size(); ++i) {
        std::vector<token> *currntToken = &thds.at(i);
        temp* currntTemp = get_temp(currnt_func);
        print_tokens(currntToken);

        if ( currntToken->at(0).type == KEYWORD && currntToken->at(0).value == "exit" ) {
            char type = chk_exit_by_number(currntToken);
            if ( type == 'n' )
                _wg_write_sys_exit_by_number(currntTemp, currntToken);
            if ( type == 'v' )
                _wg_write_sys_exit_by_variable(currntTemp, currntToken);
            if ( type == 'm' )
                type_arith_call(currntToken, currntTemp);
        }

        if ( currntToken->at(0).type == KEYWORD && currntToken->at(0).value == "wout" ) {
            char type = chk_wout(currntToken);
            if ( type == 's' ) {
                std::string namelabel = _wg_mke_string_label(dataS, currntToken->at(1).value);
                _wg_wout_operation_strings(currntTemp, namelabel);
            }
            if ( type == 'v' ) {
                _wg_wout_operation_int_variables(currntTemp, currntToken);
            }
        }

        if ( currntToken->at(0).type == VARIABLE && currntToken->at(0).value == "int" ) {
            char type = chk_int_declaration(currntToken);
            if ( type == 'n' )
                _wg_make_int_by_number(currntTemp, currntToken);
            if ( type == 'v' )
                _wg_mke_int_by_int(currntTemp, currntToken);
        }

        if ( currntToken->at(0).type == KEYWORD && currntToken->at(0).value == "printf" ) {
            chk_printf(currntToken);
            _wg_printf(currntTemp, currntToken, dataS);
        }

        /*if ( currnt->at(0).type == KEYWORD && currnt->at(0).value == "exit" ) {
            if ( chk_exit_by_number(currnt) ) _wg_exit_function_by_number(codeS, currnt->at(1).value);
            else {
                unsigned int idxstack_var = get_idx_var(currnt->at(1).value);
                _wg_exit_by_int_variable(codeS, idxstack_var);
            }
        }

        else if ( currnt->at(0).type == KEYWORD && currnt->at(0).value == "wout" ) {
            if ( chk_wout(currnt) ) {
                std::string label = make_string_label(dataS, currnt->at(1).value);
                _wg_print_string(codeS, label);
            }
            else {
                unsigned int idxstack_var = get_idx_var(currnt->at(1).value);
                _wg_print_int_variable(codeS, idxstack_var);
            }
        }

        else if ( currnt->at(0).type == VARIABLE && currnt->at(0).value == "int" ) {
            int how_create_it = chk_int_declaration(currnt);

            if ( how_create_it == 1 ) _wg_make_int_variable(codeS, currnt->at(3).value, currnt->at(1).value);
            else if ( !how_create_it ) _wg_copy_int_var_definition (codeS, currnt);
            else if ( how_create_it == 3 ) {
                std::string value = std::to_string(WG_arith(currnt));
                _wg_make_int_variable(codeS, value, currnt->at(1).value);
            }
            else if ( how_create_it == 2 ) {
                _wg_make_int_with_arith(codeS, currnt);
            }
        }

        else if ( currnt->at(0).type == KEYWORD && currnt->at(0).value == "printf" ) {
            chk_printf(currnt);
            _wg_printf(codeS, currnt->at(1).value, dataS);
        }

        else if ( currnt->at(0).type == WGPP_FUNC && currnt->at(0).value == "CHG" ) {
            char howto = chk_CHG(currnt);
            if ( howto == 'i' ) _wg_change_int_by_int(codeS, currnt);
            else if ( howto == 'n' ) _wg_change_int_by_num(codeS, currnt);
        }*/
    }

    _wg_write_all_templates(codeS);
    fclose(dataS);
    fclose(codeS);
}

#endif
