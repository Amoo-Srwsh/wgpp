#ifndef WG___ASSEMBLY_H
#define WG___ASSEMBLY_H

#include "token.h"
#include "variables.h"
#include "helps.h"
#include "assembly-templates.h"

unsigned int labl_T = 1;
std::vector<std::string> string_labls;
std::string args_r[5] = {"%esi", "%edx", "%ecx", "%r8d", "%r9d"};

void start_dataS (FILE *dataS) {
    fprintf(dataS, ".text\n");
    fprintf(dataS, ".section .rodata\n");
    fprintf(dataS, "\t.globl main\n");
    fprintf(dataS, "\t.type main, @function\n\n");

    fprintf(dataS, "\t.LPNR:\n");
    fprintf(dataS, "\t\t.string \"%%d\\n\"\n");
    fprintf(dataS, "\t\t.text\n\n");
}

std::string _wg_mke_string_label (FILE* dataS, std::string src) {
    for (size_t i = 0; i < string_labls.size(); ++i)
        if ( string_labls.at(i) == src )
            return ".LP" + std::to_string(i + 1);

    fprintf(dataS, "\t.LP%d:\n", labl_T);
    fprintf(dataS, "\t\t.string %s\n", src.c_str());
    fprintf(dataS, "\t\t.text\n\n");

    string_labls.push_back(src);
    labl_T++;
    return ".LP" + std::to_string(labl_T - 1);
}

void start_codeS (FILE *codeS) {
    fprintf(codeS, "powM:\n");
    fprintf(codeS, "\tcmp %%rdi, %%r15\n");
    fprintf(codeS, "\tjne powH\n");
    fprintf(codeS, "\tret\n");
    fprintf(codeS, "powH:\n");
    fprintf(codeS, "\timul %%r13, %%rdx\n");
    fprintf(codeS, "\tinc %%r15\n");
    fprintf(codeS, "\tjmp powM\n\n");
}

void _static_make_math_ (temp *_temp, std::vector<token> *op) {
    /* If there is a call to this function is because the program
     * gotta make some mathematical operations, the value is saved
     * on %r14d register (64 bits)*/
    if ( op->at(2).type == ID ) {
        unsigned int posStack = get_variable(op->at(2).value, NUMBER)->idxStack;
        _temp->code_ins += "\tmov -" + std::to_string(posStack) + "(%rbp), %r14\n";
    }
    else
        _temp->code_ins += "\tmov $" + op->at(2).value + ", %t14\n";

    /* i variable will point to the first mathematical operator:
     * op vector = { ARITH, (, N/V, MATH_OP, N/V, MATH_OP, ..., ) }
     *                          |        \
     *                        Number      \
     *                        or integer   \
     *                        variable      \
     *                                       \- i will point here
     *
     * For every two numbers, integer variables or both must to have a mathematical operator
     * in the middle */
    for (size_t i = 3; i < op->size() - 1; i += 2) {
        size_t poStackCurrntVar = 0;
        if ( op->at(i + 1).type == ID ) {
            poStackCurrntVar = get_variable(op->at(i + 1).value, NUMBER)->idxStack;
        }

        if ( op->at(i).value == "add" ) {
            if ( poStackCurrntVar )
                _temp->code_ins += "\tadd -" + std::to_string(poStackCurrntVar) + "(%rbp), " + "%r14d\n";
            else
                _temp->code_ins += "\tadd $" + op->at(i + 1).value + ", %r14\n";
        }

        if ( op->at(i).value == "sub" ) {
            if ( poStackCurrntVar )
                _temp->code_ins += "\tsub -" + std::to_string(poStackCurrntVar) + "(%rbp), " + "%r14d\n";
            else
                _temp->code_ins += "\tsub $" + op->at(i + 1).value + ", %r14\n";
        }

        if ( op->at(i).value == "mul" ) {
            if ( poStackCurrntVar )
                _temp->code_ins += "\timul -" + std::to_string(poStackCurrntVar) + "(%rbp), " + "%r14d\n";
            else
                _temp->code_ins += "\timul $" + op->at(i + 1).value + ", %r14\n";
        }

        if ( op->at(i).value == "div" || op->at(i).value == "mod" ) {
            _temp->code_ins += "\tmov $0, %rdx\n"
                               "\tmov %r14, %rax\n";
            if ( poStackCurrntVar )
                _temp->code_ins += "\tmov -" + std::to_string(poStackCurrntVar) + "(%rbp), %rcx\n";
            else
                _temp->code_ins += "\tmov $" + op->at(i + 1).value + ", %rcx\n";

            _temp->code_ins += "\tdiv %rcx\n";
            if ( op->at(i).value == "div" )
                _temp->code_ins += "\tmov %rax, %r14\n";
            else
                _temp->code_ins += "\tmov %rdx, %r14\n";
        }

        if ( op->at(i).value == "pot" ) {
            _temp->code_ins += "\tmov %r14, %rdx\n";
            _temp->code_ins += "\tmov %r14, %r13\n";
            if ( poStackCurrntVar )
                _temp->code_ins += "\tmov -" + std::to_string(poStackCurrntVar) + "(%rbp), %rdi\n";
            else
                _temp->code_ins += "\tmov $" + op->at(i + 1).value + ", %rdi\n";
            _temp->code_ins += "\tmov $1, %r15\n"
                               "\tcall powM\n"
                               "\tmov %rdx, %r14\n";
        }
    }
    _temp->code_ins += "\n";
}

void _wg_write_sys_exit_by_number (temp *_temp, std::vector<token> *list) {
    /* EXIT BY NUMBER (WG++)
     * code = exit 0;
     * list = {KEYWORD, NUMBER, SEMICOLON} */
    _temp->code_ins += "\tmov $60, %rax\n"
                       "\tmov $" + list->at(1).value + ", %rdi\n"
                       "\tsyscall\n\n";
}

void _wg_write_sys_exit_by_variable (temp *_temp, std::vector<token> *list) {
    /* EXIT BY NUMBER (WG++)
     * code = exit $variable$;
     * list = {KEYWORD, ID, SEMICOLON} */
    unsigned int idx = get_variable(list->at(1).value, NUMBER)->idxStack;
    _temp->code_ins += "\tmov $60, %rax\n"
                       "\tmov -" + std::to_string(idx) + "(%rbp), %rdi\n"
                       "\tsyscall\n\n";
}

void _wg_write_sys_exit_by_math_typeC (temp *_temp, int value) {
    /* EXIT BY MATH (WG++)
     * code = exit ARITH(4 add 5);
     * you can see the documentation on: ./wg_funcs.h :: void type_arith() */
    _temp->code_ins += "\tmov $60, %rax\n"
                       "\tmov $" + std::to_string(value) + ", %rdi\n"
                       "\tsyscall\n";
}

void _wg_write_sys_exit_by_math_typeA (temp *_temp, std::vector<token> *op) {
    /* EXIT BY MATH (WG++)
     * code = exit ARITH($variable$ add 5);
     * you can see the documentation on: ./wg_funcs.h :: void type_arith() */
    _static_make_math_(_temp, op);
    _temp->code_ins += "\tmov $60, %rax\n"
                       "\tmov %r14, %rdi\n"
                       "\tsyscall\n\n";
}

void _wg_wout_operation_strings (temp *_temp, std::string name_label) {
    /* WOUT (WG++)
     * code = wout "string";
     * list = {KEYWORD, STRING, SEMICOLON} */
    _temp->code_ins += "\tleaq " + name_label + "(%rip), %rax\n"
                       "\tmovq %rax, %rdi\n"
                       "\tcall puts@PLT\n"
                       "\tmovl $0, %eax\n\n";
}

void _wg_wout_operation_int_variables (temp *_temp, std::vector<token> *list) {
    /* WOUT (WG++)
     * code = wout $variable$;
     * list = {KEYWORD, ID, SEMICOLON} */
    unsigned int idx = get_variable(list->at(1).value, NUMBER)->idxStack;

    _temp->code_ins += "\tmovl -" + std::to_string(idx) + "(%rbp), %eax\n"
                       "\tmovl %eax, %esi\n"
                       "\tleaq .LPNR(%rip), %rax\n"
                       "\tmovq %rax, %rdi\n"
                       "\tmovl $0, %eax\n"
                       "\tcall printf@PLT\n"
                       "\tmovl $0, %eax\n\n" ;
}

void _wg_make_int_by_number (temp *_temp, std::vector<token> *list) {
    /* Make int by one number (WG++)
     * code = int $namevariable$ = 4;
     * list = {VARIABLE, ID, EQUALS_S, NUMBER, SEMICOLON} */
    _temp->code_ins += "\tsubq $4, %rsp\n"
                       "\tmovl $" + list->at(3).value + ", -" +
                       std::to_string(_temp->bytes_resb) + "(%rbp)\n\n";

    push_variable(_temp->bytes_resb, list->at(1).value, NUMBER);
    _temp->bytes_resb += 4;
}

void _wg_mke_int_by_int (temp *_temp, std::vector<token> *list) {
    /* Copy values among int variables (WG++)
     * code = int $y$ = $x$;
     * list = {VARIABLE, ID, EQUALS_S, ID, SEMICOLON } */
    unsigned int stack_pos = get_variable(list->at(3).value, NUMBER)->idxStack;
    _temp->code_ins += "\tsubq $4, %rsp\n"
                       "\tmovl -" + std::to_string(stack_pos) + "(%rbp), %eax\n"
                       "\tmovl %eax, -" + std::to_string(_temp->bytes_resb) + "(%rbp)\n\n";

    push_variable(_temp->bytes_resb, list->at(1).value, NUMBER);
    _temp->bytes_resb += 4;
}

void _wg_printf (temp *_temp, std::vector<token> *list, FILE* dataS) {
    /* Printf function (by GCC with the style of GW++)
     * code = printf "$anyvariable$ text $anothervariable$";
     * list = {KEYWORD, STRING, SEMICOLON} */
    std::string label_to_print = "";
    std::string strprintf = list->at(1).value;
    std::vector<std::string> args;

    for (size_t i = 0; i < strprintf.size(); ++i) {
        if ( strprintf[i] == '$' ) {
            std::string namevariable = get_name_variable(strprintf, i);
            var* thisvar = get_variable(namevariable, ANY_TYPE_VAR);

            // TODO: Make it with another type variables too
            args.push_back( std::to_string(thisvar->idxStack) );
            if ( thisvar->type_var == NUMBER )
                label_to_print += "%d";
            i += namevariable.size();
        }

        if ( strprintf[i] == '%' ) {
            label_to_print += "%%";
            i++;
        }

        label_to_print += strprintf[i];
    }

    /* Only could print 5 variables at the same time and could not
     * print 0 variables, if you dont wanna print variables and text at the same
     * time use wout instead */
    if ( args.size() >= 6 || args.size() == 0 )
        no_right_number_arguments();

    for (size_t i = 0; i < args.size(); ++i)
        _temp->code_ins += "\tmovl -" + args.at(i) + "(%rbp), " + args_r[i] + "\n";

    std::string namelabel = _wg_mke_string_label(dataS, label_to_print);
    _temp->code_ins += "\tleaq " + namelabel + "(%rip), %rax\n"
                       "\tmovq %rax, %rdi\n"
                       "\tmovl $0, %eax\n"
                       "\tcall printf@PLT\n"
                       "\tmovl $0, %eax\n\n";

    // cleaning the register
    for (size_t i = 0; i < args.size(); ++i)
        _temp->code_ins += "\tmovl $0, " + args_r[i] + "\n";
    _temp->code_ins += "\n";
}

void _wg_write_all_templates (FILE *codeS) {
    for (size_t i = 0; i < templs.size(); ++i) {
        fprintf(codeS, templs.at(i).temp_val.c_str(), templs.at(i).code_ins.c_str());
    }
}

#endif

/*
unsigned int bytes_resb = 4;

// ---------------------- DATA SECTION ------------------------ //
void start_dataS (FILE* dataS) {
    fprintf(dataS, ".text\n");
    fprintf(dataS, ".section .rodata\n");
    fprintf(dataS, "\t.globl main\n");
    fprintf(dataS, "\t.type main, @function\n");

    fprintf(dataS, "\t.LPNR:\n");
}

std::string make_string_label (FILE* dataS, const std::string src) {
    for (size_t i = 0; i < string_labls.size(); ++i)
        if ( string_labls.at(i) == src )
            return ".LP" + std::to_string(i + 1);

    fprintf(dataS, "\t.LP%d:\n", labl_T);
    fprintf(dataS, "\t\t.string %s\n", src.c_str());
    fprintf(dataS, "\t\t.text\n");

    labl_T++;
    string_labls.push_back(src);
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

}

void _wg_print_int_variable (FILE* codeS, unsigned int idxStack) {

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

        fprintf(codeS, "\tmovl $0, %%esi\n");
    fprintf(codeS, "\tmovl $0, %%ecx\n");
    fprintf(codeS, "\tmovl $0, %%edx\n");
    fprintf(codeS, "\tmovl $0, %%r8d\n");
    fprintf(codeS, "\tmovl $0, %%r9d\n");

}

void _wg_write_math_STATIC (FILE* codeS, std::vector<token> *op) {
    if ( op->at(0).type == ID ) {
        var*fv = get_variable(op->at(0).value, NUMBER);
        fprintf(codeS, "\tmov -%d(%%rbp), %%r14d\n", fv->idxStack );
    }
    else fprintf(codeS, "\tmov $%s, %%r14d\n", op->at(0).value.c_str());

    for (size_t i = 1; op->at(i).type != RIGHT_P; i += 2) {
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

                    }

        else if ( op->at(i).value == "pot" ) {

        }
    }
}

void _wg_make_int_with_arith (FILE* codeS, std::vector<token> *list)  {
    std::vector<token> operation { list->begin() + 5, list->end() - 1 };
    _wg_write_math_STATIC(codeS, &operation);

    fprintf(codeS, "\tsubq $4, %%rsp\n");
    fprintf(codeS, "\tmovl %%r14d, -%d(%%rbp)\n\n", bytes_resb);

    push_variable(bytes_resb, list->at(1).value, NUMBER);
    bytes_resb += 4;
}

void _wg_change_int_by_int (FILE* codeS, std::vector<token> *list) {
    var *fv = get_variable(list->at(1).value, NUMBER);
    var *sv = get_variable(list->at(2).value, NUMBER);
    fprintf(codeS, "\tmov -%d(%%rbp), %%rax\n", sv->idxStack);
    fprintf(codeS, "\tmov %%rax, -%d(%%rbp)\n", fv->idxStack);
    fprintf(codeS, "\tmov $0, %%rax\n");
}

void _wg_change_int_by_num (FILE* codeS, std::vector<token> *list) {
    var *fv = get_variable(list->at(1).value, NUMBER);
    fprintf(codeS, "\tmovl $%s, -%d(%%rbp)\n", list->at(2).value.c_str(), fv->idxStack);
}

void _wg_change_int_by_math (FILE* codeS, std::vector<token> *list) {
    // CHG 
    std::vector<token> operation { list->begin() + 4, list->end() - 1 };
    _wg_write_math_STATIC(codeS, &operation);

    var* fv = get_variable(list->at(1).value, NUMBER);
    fprintf(codeS, "\tmov %%r14d, -%d(%%rbp)\n",fv->idxStack);
}
*/
