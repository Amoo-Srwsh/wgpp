#ifndef WG___ASSEMBLY_H
#define WG___ASSEMBLY_H

#include "token.h"

/* Each label represents a string to be printed, we need give a unique
 * name for each one, so the name will be:
 * .LPN where N = labl_T */
unsigned int labl_T = 1;

/* Saves all labels created, it'll help us when there is a label
 * to be printed once or more times */
std::vector<std::string> labls;

// ---------------------- DATA SECTION ------------------------ //
void start_dataS (FILE* dataS) {
    fprintf(dataS, ".text\n");
    fprintf(dataS, ".section .rodata\n");
    fprintf(dataS, "\t.globl main\n");
    fprintf(dataS, "\t.type main, @function\n");

    fprintf(dataS, "\t.LPNR:\n");
    fprintf(dataS, "\t\t.string \"%%d\"\n");
    fprintf(dataS, "\t\t.text\n");
}

std::string make_string_label (FILE* dataS, const std::string src) {
    for (size_t i = 0; i < labls.size(); ++i)
        if ( labls.at(i) == src )
            return ".LP" + std::to_string(i + 1);

    fprintf(dataS, "\t.LP%d:\n", labl_T);
    fprintf(dataS, "\t\t.string %s\n", src.c_str());
    fprintf(dataS, "\t\t.text\n");

    labl_T++;
    labls.push_back(src);
    return ".LP" + std::to_string(labl_T - 1);
}

//
// ---------------------- CODE SECTION ------------------------ //
void start_codeS (FILE *codeS) {
    fprintf(codeS, "\nmain:\n");
    fprintf(codeS, "\tpushq %%rbp\n");
    fprintf(codeS, "\tmovq %%rsp, %%rbp\n");
}

void _wg_exit_function_by_number (FILE* codeS, std::string code) {
    fprintf(codeS, "\tmov $60, %%rax\n");
    fprintf(codeS, "\tmov $%s, %%rdi\n", code.c_str());
    fprintf(codeS, "\tsyscall\n\n");
}

void _wg_print_string (FILE* codeS, std::string label) {
    fprintf(codeS, "\tleaq %s(%%rip), %%rax\n", label.c_str());
    fprintf(codeS, "\tmovq %%rax, %%rdi\n");
    fprintf(codeS, "\tmovl $0, %%eax\n");
    fprintf(codeS, "\tcall puts@PLT\n");
    fprintf(codeS, "\tmovl $0, %%eax\n\n");
}

#endif
