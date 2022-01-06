#ifndef WG___ASSEMBLY_H
#define WG___ASSEMBLY_H

#include "token.h"
#include "variables.h"

/* Each label represents a string to be printed, we need give a unique
 * name for each one, so the name will be:
 * .LPN where N = labl_T */
unsigned int labl_T = 1;

/* Saves all labels created, it'll help us when there is a label
 * to be printed once or more times */
std::vector<std::string> labls;

/* We'll save the variables into the satck and each space
 * in the stack is of 4 bytes, so we need a count to know
 * in what index we are */
unsigned int bytes_resb = 4;

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

void _wg_exit_by_int_variable (FILE* codeS, unsigned int idxStack) {
    fprintf(codeS, "\tmov $60, %%rax\n");
    fprintf(codeS, "\tmov -%d(%%rbp), %%rdi\n", idxStack);
    fprintf(codeS, "\tsyscall\n\n");
}

void _wg_print_string (FILE* codeS, std::string label) {
    fprintf(codeS, "\tleaq %s(%%rip), %%rax\n", label.c_str());
    fprintf(codeS, "\tmovq %%rax, %%rdi\n");
    fprintf(codeS, "\tcall printf@PLT\n");
    fprintf(codeS, "\tmovl $0, %%eax\n\n");
}

void _wg_print_int_variable (FILE* codeS, unsigned int idxStack) {
    fprintf(codeS, "\tmovl -%d(%%rbp), %%eax\n", idxStack);
    fprintf(codeS, "\tmov %%eax, %%esi\n");
    fprintf(codeS, "\tleaq .LPNR(%%rip), %%rax\n");
    fprintf(codeS, "\tmovq %%rax, %%rdi\n");
    fprintf(codeS, "\tmovl $0, %%eax\n");
    fprintf(codeS, "\tcall printf@PLT\n");
    fprintf(codeS, "\tmovl $0, %%eax\n\n");
}

void _wg_make_int_variable (FILE* codeS, std::string value, std::string name) {
    fprintf(codeS, "\tsub $4, %%rsp\n");
    fprintf(codeS, "\tmovl $%s, -%d(%%rbp)\n\n", value.c_str(), bytes_resb);

    push_variable(bytes_resb, name);
    bytes_resb += 4;
}

#endif
