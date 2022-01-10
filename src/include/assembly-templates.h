#ifndef WG___ASSEMBLY_TEMPLATES_H
#define WG___ASSEMBLY_TEMPLATES_H

#include <iostream>
#include <vector>

enum _TemplateType {
    FUNCTION
};

typedef struct TEMAPLATE {
    _TemplateType type;
    std::string temp_val;
    std::string code_ins;

    // for functions...
    unsigned int bytes_resb;
    
} temp;
std::vector<temp> templs;
size_t currnt_tmp;

void mke_func_temp (const std::string namef) {
    temp newF;
    newF.temp_val = namef + ":\n"
                    "\tpushq   %rbp\n"
                    "\tmovq    %rsp, %rbp\n\n"
                    "%s"
                    "\tpopq %rbp\n"
                    "\tret\n\n";
    newF.type = FUNCTION;
    newF.bytes_resb = 4;
    newF.code_ins = "";

    currnt_tmp = templs.size();
    templs.push_back(newF);
}

size_t get_currnt_tmp () {
    return currnt_tmp;
}

temp* get_temp (size_t idx) {
    return &templs.at(idx);
}

#endif
