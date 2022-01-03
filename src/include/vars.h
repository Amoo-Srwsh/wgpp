#ifndef WG___VARS_H
#define WG___VARS_H

#include <iostream>
#include <vector>

typedef struct INT_VAR {
    int idx_stack;
    std::string name;
} i_var;
std::vector<i_var> Ivars;

void push_var (std::string name, int s) {
    i_var x;
    x.name = name;
    x.idx_stack = s;

    Ivars.push_back(x);
}

int get_idx_stack (std::string name) {
    for (size_t i = 0; i < Ivars.size(); ++i) {
        if (Ivars.at(i).name == name) {
            return Ivars.at(i).idx_stack;
        }
    }
    return -1;
}


#endif
