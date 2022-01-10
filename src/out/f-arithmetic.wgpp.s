.text
.section .rodata
	.globl main
	.type main, @function

	.LPNR:
		.string "%d\n"
		.text

powM:
	cmp %rdi, %r15
	jne powH
	ret
powH:
	imul %r13, %rdx
	inc %r15
	jmp powM

main:
	pushq   %rbp
	movq    %rsp, %rbp

	subq $4, %rsp
	movl $4, -4(%rbp)

	mov -4(%rbp), %r14
	mov %r14, %rdx
	mov %r14, %r13
	mov -4(%rbp), %rdi
	mov $1, %r15
	call powM
	mov %rdx, %r14
    dec %r14

	mov $60, %rax
	mov %r14, %rdi
	syscall

	popq %rbp
	ret

