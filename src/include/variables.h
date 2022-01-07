#ifndef WG___VARIABLES_H
#define WG___VARIABLES_H

#include "err-report.h"
#include "token.h"

typedef struct VARIABLE {
    unsigned int idxStack;
    std::string name;
    _TokenType type_var;
} var;
std::vector<var>  variables;

void push_variable (unsigned int idxS, std::string name, _TokenType t) {
    var newvar;
    newvar.idxStack = idxS;
    newvar.name = name;
    newvar.type_var = t;

    variables.push_back(newvar);
}

unsigned int get_idx_var (std::string name) {
    for (size_t i = 0; i < variables.size(); ++i)
        if ( variables.at(i).name == name )
            return variables.at(i).idxStack;

    var_doesnt_exist(name);
    return -1;
}

#endif
