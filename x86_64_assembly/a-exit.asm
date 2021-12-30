section .text
    global _start

_start:
    mov rax, 60     ; syscall to exit
    mov rdi, 0      ; code error
    syscall
