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

var* get_variable (std::string name, _TokenType type) {
    var* varet = nullptr;
    for (size_t i = 0; i < variables.size(); ++i) {
        if ( variables.at(i).name == name ) {
            varet = &variables.at(i);
            break;
        }
    }

    if ( varet == nullptr ) var_doesnt_exist(name);
    if ( type == ANY_TYPE_VAR && varet != nullptr ) return varet;
    if ( varet->type_var == type ) return varet;
    if ( varet->type_var != type ) wrong_type_argument();

    return nullptr;
}

#endif
