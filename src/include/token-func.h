#ifndef WG___TOKEN_FUNC_H
#define WG___TOKEN_FUNC_H

#include "token.h"
#include "assembly.h"
#include "SCH.h"
#include "variables.h"

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

    for (size_t i = 0; i < thds.size(); ++i) {
        std::vector<token> *currnt = &thds.at(i);
        print_tokens(currnt);

        if ( currnt->at(0).type == KEYWORD && currnt->at(0).value == "exit" ) {
            if ( chk_exit_by_number(currnt) ) _wg_exit_function_by_number(codeS, currnt->at(1).value);
            else {
                unsigned int idxstack_var = get_idx_var(currnt->at(1).value);
                _wg_exit_by_int_variable(codeS, idxstack_var);
            }
        }

        if ( currnt->at(0).type == KEYWORD && currnt->at(0).value == "wout" ) {
            if ( chk_print(currnt) ) {
                std::string label = make_string_label(dataS, currnt->at(1).value);
                _wg_print_string(codeS, label);
            }
            else {
                unsigned int idxstack_var = get_idx_var(currnt->at(1).value);
                _wg_print_int_variable(codeS, idxstack_var);
            }
        }

        if ( currnt->at(0).type == VARIABLE && currnt->at(0).value == "int" ) {
            if ( chk_int_declaration(currnt) ) {
                _wg_make_int_variable(codeS, currnt->at(3).value, currnt->at(1).value);
            }
        }

    }

    fclose(dataS);
    fclose(codeS);
}

#endif
