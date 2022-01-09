.text
.section .rodata
	.globl main
	.type main, @function
	.LPNR:
		.string "%d"
		.text

pot:
    cmp %rdi, %r15
    jne power

    ret

power:
    imul %r14, %rdx
    inc %r15
    jmp pot

main:
	pushq %rbp
	movq %rsp, %rbp

    # count, hasta, n, nn
    mov $4, %rdx   # n
    mov $4, %r14   # nn

    mov $3, %rdi  # nn
    mov $1, %r15  # count
    call pot

    mov $60, %rax
    mov %rdx, %rdi
    syscall
	#mov $60, %rax
	#mov $16, %rdi
	#syscall

	#mov $60, %rax
	#mov $-3, %rdi
	#syscall

