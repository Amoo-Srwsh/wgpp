#ifndef WG___ASM_H
#define WG___ASM_H

#include <iostream>

int labelSTR_TO_PRINT = 1;

void init_asm1 (FILE *asm1) {
    fprintf(asm1, "section .text\n");
    fprintf(asm1, "\tglobal _start\n");
    fprintf(asm1, "_start:\n");
}

void _wg_exit_by_number (FILE* asm1, const std::string exitstatus) {
    fprintf(asm1, "\tmov rax, 60\n");
    fprintf(asm1, "\tmov rdi, %s\n", exitstatus.c_str());
    fprintf(asm1, "\tsyscall\n");
}

void _wg_print_by_str (FILE* asm2, const std::string buffer, int length) {
    fprintf(asm2, "\tmov rax, 1\n");
    fprintf(asm2, "\tmov rdi, 1\n");
    fprintf(asm2, "\tmov rsi, %s\n", buffer.c_str());
    fprintf(asm2, "\tmov rdx, %d\n", length);
    fprintf(asm2, "\tsyscall\n");
}



// -------------------------------------------------------------------------------------------------- //


void init_asm2 (FILE *asm2) {
    fprintf(asm2, "\n\n;---------------------------------------------------- PRINT NUMBER CODE ----------------------------------------------- ;\n");
    fprintf(asm2, "PrintNumber:\n");
    fprintf(asm2, "\tsub rsp, 40\n");
    fprintf(asm2, "\tmov rcx, rdi\n");
    fprintf(asm2, "\txor r11d, r11d\n");
    fprintf(asm2, "\ttest edi, edi\n");
    fprintf(asm2, "\tjns .PN2\n");
    fprintf(asm2, "\tneg rcx\n");
    fprintf(asm2, "\tmov r11d, 1\n");

    fprintf(asm2, ".PN2:\n");
    fprintf(asm2, "\tmov r8d, 1\n");
    fprintf(asm2, "\tlea r10, [rsp+31]\n");
    fprintf(asm2, "\tmov r9, -3689348814741910323\n");

    fprintf(asm2, ".PN3:\n");
    fprintf(asm2, "\tmov rax, rcx\n");
    fprintf(asm2, "\tmov rdi, r10\n");
    fprintf(asm2, "\tmul r9\n");
    fprintf(asm2, "\tmov rax, rcx\n");
    fprintf(asm2, "\tsub rdi, r8\n");
    fprintf(asm2, "\tshr rdx, 3\n");
    fprintf(asm2, "\tlea rsi, [rdx+rdx*4]\n");
    fprintf(asm2, "\tadd rsi, rsi\n");
    fprintf(asm2, "\tsub rax, rsi\n");
    fprintf(asm2, "\tmov rsi, r8\n");
    fprintf(asm2, "\tadd r8, 1\n");
    fprintf(asm2, "\tadd eax, 48\n");
    fprintf(asm2, "\tmov BYTE  [rdi], al\n");
    fprintf(asm2, "\tmov rax, rcx\n");
    fprintf(asm2, "\tmov rcx, rdx\n");
    fprintf(asm2, "\tcmp rax, 9\n");
    fprintf(asm2, "\tja .PN3\n");
    fprintf(asm2, "\ttest r11d, r11d\n");
    fprintf(asm2, "\tjne .PN4\n");
    fprintf(asm2, "\tmov eax, 32\n");
    fprintf(asm2, "\tsub rax, r8\n");

    fprintf(asm2, ".PN5:\n");
    fprintf(asm2, "\tlea rsi, [rsp+rax]\n");
    fprintf(asm2, "\tmov rdx, r8\n");
    fprintf(asm2, "\tmov edi, 1\n");
    fprintf(asm2, "\tmov rax, 1\n");
    fprintf(asm2, "\tsyscall\n");
    fprintf(asm2, "\tadd rsp, 40\n");
    fprintf(asm2, "\tret\n");

    fprintf(asm2, ".PN4:\n");
    fprintf(asm2, "\tlea r8, [rsi+2]\n");
    fprintf(asm2, "\tmov eax, 32\n");
    fprintf(asm2, "\tsub rax, r8\n");
    fprintf(asm2, "\tmov BYTE  [rsp+rax], 45\n");
    fprintf(asm2, "\tjmp .PN5\n");
    fprintf(asm2, "; ---------------------------------------------------- PRINT NUMBER CODE ----------------------------------------------- ;\n\n");

    fprintf(asm2, "section .data\n");
}

std::string _wg_label_string (FILE* asm2, const std::string code_str) {
    // lsp = label string print
    std::string currentLSP = "lsp";
    currentLSP += std::to_string(labelSTR_TO_PRINT);

    fprintf(asm2, "\t%s db %s\n", currentLSP.c_str(), code_str.c_str());
    labelSTR_TO_PRINT++;

    return currentLSP;
}


#endif
