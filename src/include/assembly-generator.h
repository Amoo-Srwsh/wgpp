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

    fprintf(dataS, "\t.data\n");
    fprintf(dataS, "\t.type .auxINT, @object\n");
    fprintf(dataS, "\t.auxINT:\n");
    fprintf(dataS, "\t\t.long 0\n");
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
    fprintf(codeS, "# ------------------------------------------- POWER OPERATION -------------------------------------------\n");
    fprintf(codeS, "powM:\n");
    fprintf(codeS, "\tcmpl $0, %%edi\n");
    fprintf(codeS, "\tje powE_by_0\n");
    fprintf(codeS, "\tcmpl $-1, %%edi\n");
    fprintf(codeS, "\tjle powE_by_SN\n");
    fprintf(codeS, "\tcmpl %%edi, %%r15d\n");
    fprintf(codeS, "\tjne powH\n");
    fprintf(codeS, "\tret\n");

    fprintf(codeS, "powH:\n");
    fprintf(codeS, "\timul %%r13d, %%edx\n");
    fprintf(codeS, "\tincl %%r15d\n");
    fprintf(codeS, "\tjmp powM\n");

    fprintf(codeS, "powE_by_0:\n");
    fprintf(codeS, "\tmovl $1, %%edx\n");
    fprintf(codeS, "\tret\n");

    fprintf(codeS, "powE_by_SN:\n");
    fprintf(codeS, "\tcmpl $-1, %%edx\n");
    fprintf(codeS, "\tje powE_by_Sone\n");
    fprintf(codeS, "\tcmpl $1, %%edx\n");
    fprintf(codeS, "\tje powE_by_USone\n");
    fprintf(codeS, "\tmovl $0, %%edx\n");
    fprintf(codeS, "\tret\n");

    fprintf(codeS, "powE_by_Sone:\n");
    fprintf(codeS, "\tmovl $-1, %%edx\n");
    fprintf(codeS, "\tret\n");

    fprintf(codeS, "powE_by_USone:\n");
    fprintf(codeS, "\tmovl $1, %%edx\n");
    fprintf(codeS, "\tret\n");

    fprintf(codeS, "return_help:\n");
    fprintf(codeS, "\tret\n");
    fprintf(codeS, "check_pwer_abs:\n");
    fprintf(codeS, "\tcmpl $1, %%edx\n");
    fprintf(codeS, "\tjge return_help\n");
    fprintf(codeS, "\tnegl %%r13d\n");
    fprintf(codeS, "\tret\n");
    fprintf(codeS, "# ------------------------------------------- POWER OPERATION -------------------------------------------\n");
}

void _static_make_math_ (temp *_temp, std::vector<token> *op) {
    /* If there is a call to this function is because the program
     * gotta make some mathematical operations, the value is saved
     * on %r14d register (64 bits)*/
    if ( op->at(2).type == ID ) {
        unsigned int posStack = get_variable(op->at(2).value, NUMBER)->idxStack;
        _temp->code_ins += "\tmovl -" + std::to_string(posStack) + "(%rbp), %r14d\n";
    }
    else
        _temp->code_ins += "\tmovl $" + op->at(2).value + ", %r14d\n";

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
                _temp->code_ins += "\taddl -" + std::to_string(poStackCurrntVar) + "(%rbp), " + "%r14d\n";
            else
                _temp->code_ins += "\taddl $" + op->at(i + 1).value + ", %r14d\n";
        }

        if ( op->at(i).value == "sub" ) {
            if ( poStackCurrntVar )
                _temp->code_ins += "\tsubl -" + std::to_string(poStackCurrntVar) + "(%rbp), " + "%r14d\n";
            else
                _temp->code_ins += "\tsubl $" + op->at(i + 1).value + ", %r14d\n";
        }

        if ( op->at(i).value == "mul" ) {
            if ( poStackCurrntVar )
                _temp->code_ins += "\timull -" + std::to_string(poStackCurrntVar) + "(%rbp), " + "%r14d\n";
            else
                _temp->code_ins += "\timull $" + op->at(i + 1).value + ", %r14d\n";
        }

        if ( op->at(i).value == "div" || op->at(i).value == "mod" ) {
            _temp->code_ins += "\tmovl $0, %edx\n"
                               "\tmovl %r14d, %eax\n";
            if ( poStackCurrntVar )
                _temp->code_ins += "\tmovl -" + std::to_string(poStackCurrntVar) + "(%rbp), %ecx\n";
            else
                _temp->code_ins += "\tmovl $" + op->at(i + 1).value + ", %ecx\n";

            _temp->code_ins += "\tdivl %ecx\n";
            if ( op->at(i).value == "div" )
                _temp->code_ins += "\tmovl %eax, %r14d\n";
            else
                _temp->code_ins += "\tmovl %edx, %r14d\n";
        }

        if ( op->at(i).value == "pot" ) {
            _temp->code_ins += "\tmovl %r14d, %edx\n";
            _temp->code_ins += "\tmovl %r14d, %r13d\n";
            if ( poStackCurrntVar )
                _temp->code_ins += "\tmovl -" + std::to_string(poStackCurrntVar) + "(%rbp), %edi\n";
            else
                _temp->code_ins += "\tmovl $" + op->at(i + 1).value + ", %edi\n";
            _temp->code_ins += "\tmovl $1, %r15d\n"
                               "\tcall check_pwer_abs\n"
                               "\tcall powM\n"
                               "\tmovl %edx, %r14d\n";
        }
    }
    _temp->code_ins += "\n";
}

void _wg_write_sys_exit_by_number (temp *_temp, std::vector<token> *list) {
    /* EXIT BY NUMBER (WG++)
     * code = exit 0;
     * list = {KEYWORD, NUMBER, SEMICOLON} */
    _temp->code_ins += "\tmovq $60, %rax\n"
                       "\tmovq $" + list->at(1).value + ", %rdi\n"
                       "\tsyscall\n\n";
}

void _wg_write_sys_exit_by_variable (temp *_temp, std::vector<token> *list) {
    /* EXIT BY NUMBER (WG++)
     * code = exit $variable$;
     * list = {KEYWORD, ID, SEMICOLON} */
    unsigned int idx = get_variable(list->at(1).value, NUMBER)->idxStack;
    _temp->code_ins += "\tmovq $60, %rax\n"
                       "\tmovq -" + std::to_string(idx) + "(%rbp), %rdi\n"
                       "\tsyscall\n\n";
}

void _wg_write_sys_exit_by_math_typeC (temp *_temp, int value) {
    /* EXIT BY MATH (WG++)
     * code = exit ARITH(4 add 5);
     * you can see the documentation on: ./wg_funcs.h :: void type_arith() */
    _temp->code_ins += "\tmovq $60, %rax\n"
                       "\tmovq $" + std::to_string(value) + ", %rdi\n"
                       "\tsyscall\n";
}

void _wg_write_sys_exit_by_math_typeA (temp *_temp, std::vector<token> *op) {
    /* EXIT BY MATH (WG++)
     * code = exit ARITH($variable$ add 5);
     * you can see the documentation on: ./wg_funcs.h :: void type_arith() */
    _static_make_math_(_temp, op);
    _temp->code_ins += "\tmovl %r14d, .auxINT(%rip)\n"
                       "\tmovq $60, %rax\n"
                       "\tmovq .auxINT(%rip), %rdi\n"
                       "\tsyscall\n"
                       "\tmovl $0, .auxINT(%rip)\n\n";
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

void _wg_wout_operation_math_typeC (temp *_temp, int value) {
    /* WOUT MATH (WG++)
     * code = wout ARITH(4 sub 4 add 4); */
    _temp->code_ins += "\tmovl $" + std::to_string(value) + ", %eax\n"
                       "\tmovl %eax, %esi\n"
                       "\tleaq .LPNR(%rip), %rax\n"
                       "\tmovq %rax, %rdi\n"
                       "\tmovl $0, %eax\n"
                       "\tcall printf@PLT\n"
                       "\tmovl $0, %eax\n\n";
}

void _wg_wout_operation_math_typeA (temp *_temp, std::vector<token> *op) {
    /* WOUT MATH (WG++)
     * code = wout ARITH(4 sub 4 add $variable$); */
    _static_make_math_(_temp, op);
    _temp->code_ins += "\tmovl %r14d, %eax\n"
                       "\tmovl %eax, %esi\n"
                       "\tleaq .LPNR(%rip), %rax\n"
                       "\tmovq %rax, %rdi\n"
                       "\tmovl $0, %eax\n"
                       "\tcall printf@PLT\n"
                       "\tmovl $0, %eax\n\n";
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

void _wg_mke_int_by_math_typeC (temp* _temp, int value, std::string name) {
    /* INT MATH (WG++)
     * code = int $x$ = ARITH(4 add 5); */
    _temp->code_ins += "\tsubq $4, %rsp\n"
                       "\tmovl $" + std::to_string(value) + ", -" +
                       std::to_string(_temp->bytes_resb) + "(%rbp)\n\n";

    push_variable(_temp->bytes_resb, name, NUMBER);
    _temp->bytes_resb += 4;
}

void _wg_mke_int_by_math_typeA (temp *_temp, std::vector<token> *op, std::string name) {
    /* INT MATH (WG++)
     * code = int $x$ = 4;
     *        int $y$ = ARITH($x$ mod 2); */
    _static_make_math_(_temp, op);
    _temp->code_ins += "\tsubq $4, %rsp\n"
                       "\tmovl %r14d, -" + std::to_string(_temp->bytes_resb) + "(%rbp)\n\n";

    push_variable(_temp->bytes_resb, name, NUMBER);
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

            // TODO: Make it with strings and pointers when are already
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

void _wg_chg_int_by_number (temp* _temp, std::vector<token> *list) {
    /* CHG (WG++)
     * code = int $v$ = 4;
     *        CHG $v$ 6;
     * list = {WGPP_FUNC, ID, NUMBER}
     * Works to change the value of one variale */
    var* variable = get_variable(list->at(1).value, NUMBER);
    _temp->code_ins += "\tmovl $" + list->at(2).value + ", %eax\n"
                       "\tmovl %eax, -" + std::to_string(variable->idxStack) + "(%rbp)\n\n";
}

void _wg_chg_int_by_int (temp *_temp, std::vector<token> *list) {
    /* CHG (WG++)
     * code = int $v$ = 4;
     *        int $vv$ = 5;
     *        CHG $v$ $vv$;
     * list = {WGPP_FUNC, ID, NUMBER}
     * Works to change the value of one variale */
    var* v1 = get_variable(list->at(1).value, NUMBER);
    var* v2 = get_variable(list->at(2).value, NUMBER);

    _temp->code_ins += "\tmovl -" + std::to_string(v2->idxStack) + "(%rbp), %eax\n"
                       "\tmovl %eax, -" + std::to_string(v1->idxStack) + "(%rbp)\n\n";
}

void _wg_chg_int_by_math_typeC (temp* _temp, int value, std::string namev) {
    /* CHG (WG++)
     * code = int $v$ = 4;
     *        CHG $v$ ARITH(4 sub 45);
     * Works to change the value of one variale */
    var* variable = get_variable(namev, NUMBER);
    _temp->code_ins += "\tmovl $" + std::to_string(value) + ", %eax\n"
                       "\tmovl %eax, -" + std::to_string(variable->idxStack) + "(%rbp)\n\n";
}

void _wg_chg_int_by_math_typeA (temp* _temp, std::vector<token> *op, std::string namev) {
    /* CHG (WG++)
     * code = int $v$ = 4;
     *        CHG $v$ ARITH(4 sub $v$);
     * Works to change the value of one variale */
    var* variable = get_variable(namev, NUMBER);
    _static_make_math_(_temp, op);

    _temp->code_ins += "\tmovl %r14d, %eax\n"
                       "\tmovl %eax, -" + std::to_string(variable->idxStack) + "(%rbp)\n\n";
}

void _wg_write_all_templates (FILE *codeS) {
    for (size_t i = 0; i < templs.size(); ++i) {
        fprintf(codeS, templs.at(i).temp_val.c_str(), templs.at(i).code_ins.c_str());
    }
}

#endif
