#ifndef WG___TOKEN_FUNC_H
#define WG___TOKEN_FUNC_H

#include "token.h"
#include "assembly.h"
#include "SCH.h"

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

        if ( currnt->at(0).type == KEYWORD && currnt->at(0).value == "exit" ) {
            if ( chk_exit_by_number(currnt) == 1 ) {
                _wg_exit_function_by_number(codeS, currnt->at(1).value);
            }
        }

        if ( currnt->at(0).type == KEYWORD && currnt->at(0).value == "print" ) {
            if ( chk_print(currnt) == 1 ) {
                std::string label = make_string_label(dataS, currnt->at(1).value);
                _wg_print_string(codeS, label);
            }
        }



        print_tokens(currnt);
    }

    fclose(dataS);
    fclose(codeS);
}

#endif
