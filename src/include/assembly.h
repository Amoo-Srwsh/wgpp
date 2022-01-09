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
std::string math_r[5] = {"%eax", "%ebx", "%ecx", "%edx", "%esi"};

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
    fprintf(codeS, "pot:\n");
    fprintf(codeS, "\tcmp %%edi, %%r15d\n");
    fprintf(codeS, "\tjne pow\n");
    fprintf(codeS, "\tret\n");

    fprintf(codeS, "pow:\n");
    fprintf(codeS, "\timul %%r13d, %%edx\n");
    fprintf(codeS, "\tinc %%r15d\n");
    fprintf(codeS, "\tjmp pot\n");

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

void _wg_make_int_variable (FILE* codeS, std::string value, std::string name) {
    fprintf(codeS, "\tsubq $4, %%rsp\n");
    fprintf(codeS, "\tmovl $%s, -%d(%%rbp)\n\n", value.c_str(), bytes_resb);

    push_variable(bytes_resb, name, NUMBER);
    bytes_resb += 4;
}

void _wg_copy_int_var_definition (FILE* codeS, std::vector<token> *line) {
    unsigned int idxSvar = get_idx_var(line->at(3).value);
    fprintf(codeS, "\tsubq $4, %%rsp\n");
    fprintf(codeS, "\tmovl -%d(%%rbp), %%eax\n", idxSvar);
    fprintf(codeS, "\tmovl %%eax, -%d(%%rbp)\n", bytes_resb);
    fprintf(codeS, "\tmovl $0, %%eax\n");

    push_variable(bytes_resb, line->at(1).value, NUMBER);
    bytes_resb += 4;
}

void _wg_printf (FILE* codeS, std::string str, FILE* dataS) {
    std::string lpc = "";
    std::vector<var> vars_to_print;

    for (size_t i = 0; i < str.size(); ++i) {
        if ( str[i] == '$' ) {
            std::string namevar = get_name_variable(str, i);
            vars_to_print.push_back( *get_variable(namevar, ANY_TYPE_VAR) );


            // TODO: print strings variables too
            if ( vars_to_print.at(vars_to_print.size() - 1).type_var == NUMBER )
                lpc.append("%d");
            i += namevar.size();
        }

        if ( str[i] == '%' ) {
            lpc += str[i];
            lpc += '%';
            i++;
        }

        lpc += str[i];
    }

    std::string label = make_string_label(dataS, lpc);
    if ( vars_to_print.size() >= 6 || vars_to_print.size() == 0 )
        no_right_number_arguments();

    for (size_t i = 0; i < vars_to_print.size(); ++i)
        fprintf(codeS, "\tmovl -%d(%%rbp), %s\n", vars_to_print.at(i).idxStack, args_r[i].c_str());

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

void _wg_write_math (FILE* codeS, std::vector<token> *op) {
    std::vector<var> variables;
    if ( op->at(5).type == ID ) {
        variables.push_back( *get_variable(op->at(5).value, NUMBER) );
        fprintf(codeS, "\tmov -%d(%%rbp), %%r14d\n", variables.at(0).idxStack);
    }
    else fprintf(codeS, "\tmov $%s, %%r14d\n", op->at(5).value.c_str());

    for (size_t i = 6; op->at(i).type != RIGHT_P; i += 2) {
        var* theres_var = nullptr;
        if ( op->at(i + 1).type == ID ) {
            theres_var = get_variable(op->at(i + 1).value, NUMBER);
        }

        if ( op->at(i).value == "mul" ) {
            if ( theres_var == nullptr )
                fprintf(codeS, "\timul $%s, %%r14d\n", op->at(i + 1).value.c_str());
            else
                fprintf(codeS, "\timul -%d(%%rbp), %%r14d\n", theres_var->idxStack);
        }

        else if ( op->at(i).value == "add" ) {
            if ( theres_var == nullptr )
                fprintf(codeS, "\tadd $%s, %%r14d\n", op->at(i + 1).value.c_str());
            else
                fprintf(codeS, "\tadd -%d(%%rbp), %%r14d\n", theres_var->idxStack);
        }

        else if ( op->at(i).value == "sub" ) {
            if ( theres_var == nullptr )
                fprintf(codeS, "\tsub $%s, %%r14d\n", op->at(i + 1).value.c_str());
            else
                fprintf(codeS, "\tsub -%d(%%rbp), %%r14d\n", theres_var->idxStack);
        }
        
        else if ( op->at(i).value == "div" || op->at(i).value == "mod" ) {
            fprintf(codeS, "\tmov $0, %%edx\n");
            fprintf(codeS, "\tmov %%r14d, %%eax\n");

            if ( theres_var == nullptr )
                fprintf(codeS, "\tmov $%s, %%ecx\n", op->at(i + 1).value.c_str());
            else
                fprintf(codeS, "\tmov -%d(%%rbp), %%ecx\n", theres_var->idxStack);

            fprintf(codeS, "\tdiv %%ecx\n");
            if ( op->at(i).value == "div" )
                fprintf(codeS, "\tmov %%eax, %%r14d\n");
            else
                fprintf(codeS, "\tmov %%edx, %%r14d\n");
        }

        else if ( op->at(i).value == "pot" ) {
            fprintf(codeS, "\tmov %%r14d, %%edx\n");
            fprintf(codeS, "\tmov %%r14d, %%r13d\n");
            if ( theres_var )
                fprintf(codeS, "\tmov -%d(%%rbp), %%edi\n", theres_var->idxStack);
            else
                fprintf(codeS, "\tmov $%s, %%edi\n", op->at(i + 1).value.c_str());
            fprintf(codeS, "\tmov $1, %%r15d\n");
            fprintf(codeS, "\tcall pot\n");
            fprintf(codeS, "\tmov %%edx, %%r14d\n");
        }
    }

    fprintf(codeS, "\tsubq $4, %%rsp\n");
    fprintf(codeS, "\tmovl %%r14d, -%d(%%rbp)\n\n", bytes_resb);

    push_variable(bytes_resb, op->at(1).value, NUMBER);
    bytes_resb += 4;
}

#endif
