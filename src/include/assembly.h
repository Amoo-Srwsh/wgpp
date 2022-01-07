#ifndef WG___ASSEMBLY_H
#define WG___ASSEMBLY_H

#include "token.h"
#include "variables.h"
#include "helps.h"

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

std::string args_r[5] = {"%esi", "%edx", "%ecx", "%r8d", "%r9d"};

// ---------------------- DATA SECTION ------------------------ //
void start_dataS (FILE* dataS) {
    fprintf(dataS, ".text\n");
    fprintf(dataS, ".section .rodata\n");
    fprintf(dataS, "\t.globl main\n");
    fprintf(dataS, "\t.type main, @function\n");

    fprintf(dataS, "\t.LPNR:\n");
    fprintf(dataS, "\t\t.string \"%%d\\n\"\n");
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
    fprintf(codeS, "\tcall puts@PLT\n");
    fprintf(codeS, "\tmovl $0, %%eax\n\n");
}

void _wg_print_int_variable (FILE* codeS, unsigned int idxStack) {
    fprintf(codeS, "\tmovl -%d(%%rbp), %%eax\n", idxStack);
    fprintf(codeS, "\tmovl %%eax, %%esi\n");
    fprintf(codeS, "\tleaq .LPNR(%%rip), %%rax\n");
    fprintf(codeS, "\tmovq %%rax, %%rdi\n");
    fprintf(codeS, "\tmovl $0, %%eax\n");
    fprintf(codeS, "\tcall printf@PLT\n");
    fprintf(codeS, "\tmovl $0, %%eax\n\n");
}

void _wg_make_int_variable (FILE* codeS, std::string value, std::string name, _TokenType t) {
    fprintf(codeS, "\tsubq $4, %%rsp\n");
    fprintf(codeS, "\tmovl $%s, -%d(%%rbp)\n\n", value.c_str(), bytes_resb);

    push_variable(bytes_resb, name, t);
    bytes_resb += 4;
}

void _wg_copy_int_values (FILE* codeS, std::vector<token> *line, _TokenType t) {
    unsigned int idxSvar = get_idx_var(line->at(3).value);
    fprintf(codeS, "\tsubq $4, %%rsp\n");
    fprintf(codeS, "\tmovl -%d(%%rbp), %%eax\n", idxSvar);
    fprintf(codeS, "\tmovl %%eax, -%d(%%rbp)\n", bytes_resb);
    fprintf(codeS, "\tmovl $0, %%eax\n");

    push_variable(bytes_resb, line->at(1).value, t);
    bytes_resb += 4;
}

void _wg_printf (FILE* codeS, std::string str, FILE* dataS) {
    std::string lpc = "";
    std::vector<var> vars_to_print;

    for (size_t i = 0; i < str.size(); ++i) {
        if ( str[i] == '$' ) {
            std::string namevar = get_name_variable(str, i);
            vars_to_print.push_back( *get_variable(namevar) );

            // TODO: print strings too
            if ( vars_to_print.at(vars_to_print.size() - 1).type_var == NUMBER )
                lpc.append("%d");
            i += namevar.size();
        }
        lpc += str[i];
    }

    std::string label = make_string_label(dataS, lpc);
    if ( vars_to_print.size() >= 6 )
        no_right_number_arguments();

    for (size_t i = 0; i < vars_to_print.size(); ++i) {
        fprintf(codeS, "\tmovl -%d(%%rbp), %s\n", vars_to_print.at(i).idxStack, args_r[i].c_str());
    }

    fprintf(codeS, "\tleaq %s(%%rip), %%rax\n", label.c_str());
    fprintf(codeS, "\tmovq %%rax, %%rdi\n");
    fprintf(codeS, "\tmovl $0, %%eax\n");
    fprintf(codeS, "\tcall printf@PLT\n");
    fprintf(codeS, "\tmovl $0, %%eax\n");

    fprintf(codeS, "\tmovl $0, %%esi\n");
    fprintf(codeS, "\tmovl $0, %%ecx\n");
    fprintf(codeS, "\tmovl $0, %%edx\n");
    fprintf(codeS, "\tmovl $0, %%r8d\n");
    fprintf(codeS, "\tmovl $0, %%r9d\n");
}

#endif
