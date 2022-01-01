; This section saves all static values and contants, could be more :D, i'll know it
section .data
    msg db "Any message", 0xa ; could be a string or the ascii code of each character

section .text
    global _start
_start:
    mov rax, 1     ; sys_write
    mov rdi, 1     ; output
    mov rsi, msg   ; buffer
    mov rdx, 12    ; n chars of the buffer
    syscall

    mov rax, 60
    mov rdi, 0
    syscall
