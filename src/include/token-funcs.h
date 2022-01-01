#ifndef WG___TOKEN_FUNCS_H
#define WG___TOKEN_FUNCS_H

#include "token.h"
#include "asm.h"
#include "check.h"
#include "utils.h"
#include <cmath>

int get_headidx () {
    Thead.push_back( std::vector<token>() );
    return Thead.size() - 1;
}

void push_token (int idx, TokenType type, std::string value) {
    token* nt = new (struct TOKEN);
    nt->type = type;
    nt->value = value;

    Thead.at(idx).push_back(*nt);
}

void parser () {
    FILE *asm_p1 = fopen("asmp1.asm", "w");
    FILE *asm_p2 = fopen("asmp2.asm", "w");

    init_asm1(asm_p1);
    init_asm2(asm_p2);

    for (size_t i = 0; i < Thead.size(); ++i) {
        std::vector<token> *current = &Thead.at(i);

        if ( current->at(0).type == EXIT_FUNCTION ) {
            if ( exit_function_by_number(current) ) {
                _wg_exit_by_number( asm_p1, current->at(1).value );
            }
            // TODO: exit with variable
        }

        if ( current->at(0).type == PRINT_FUNCTION ) {
            if ( print_function_by_str(current) ) {
                int length;
                std::string asmstr = parse_str_to_strASM(current->at(1).value, &length);
                std::string namelabel = _wg_label_string(asm_p2, asmstr);

                _wg_print_by_str(asm_p1, namelabel, length);
            }
        }




        for (size_t j = 0; j < Thead.at(i).size(); ++j) {
            printf("(%s :: %d), ", Thead.at(i).at(j).value.c_str(), Thead.at(i).at(j).type);
        }
        printf("\n");

    }

    fclose(asm_p1);
    fclose(asm_p2);
}


#endif
