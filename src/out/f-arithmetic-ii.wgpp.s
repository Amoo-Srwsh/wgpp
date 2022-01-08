.text
.section .rodata
	.globl main
	.type main, @function
	.LPNR:
		.string "%d\n"
		.text
	.LP1:
		.string "x variable is equals to %d\n"
		.text
	.LP2:
		.string "y variable is equals to %d\n"
		.text
	.LP3:
		.string "z variable is equals to %d\n"
		.text
	.LP4:
		.string "another variable is equals to %d\n"
		.text
	.LP5:
		.string "another2 variable is equals to %d\n"
		.text
	.LP6:
		.string "megaSUB variable is equals to %d\n"
		.text

main:
	pushq %rbp
	movq %rsp, %rbp
	subq $4, %rsp
	movl $10, -4(%rbp)

	mov -4(%rbp), %r14d
	imul -4(%rbp), %r14d
	add $16, %r14d
	add $4, %r14d
	subq $4, %rsp
	movl %r14d, -8(%rbp)

	mov -8(%rbp), %r14d
	sub -4(%rbp), %r14d
	subq $4, %rsp
	movl %r14d, -12(%rbp)

	mov -8(%rbp), %r14d
	mov $0, %edx
	mov %r14d, %eax
	mov $10, %ecx
	div %ecx
	mov %edx, %r14d
	subq $4, %rsp
	movl %r14d, -16(%rbp)

	mov -4(%rbp), %r14d
	mov $0, %edx
	mov %r14d, %eax
	mov $2, %ecx
	div %ecx
	mov %eax, %r14d
	subq $4, %rsp
	movl %r14d, -20(%rbp)

	mov -4(%rbp), %r14d
	sub -8(%rbp), %r14d
	sub -12(%rbp), %r14d
	sub -16(%rbp), %r14d
	sub -20(%rbp), %r14d
	subq $4, %rsp
	movl %r14d, -24(%rbp)

	movl -4(%rbp), %esi
	leaq .LP1(%rip), %rax
	movq %rax, %rdi
	movl $0, %eax
	call printf@PLT
	movl $0, %eax
	movl $0, %esi
	movl $0, %ecx
	movl $0, %edx
	movl $0, %r8d
	movl $0, %r9d
	movl -8(%rbp), %esi
	leaq .LP2(%rip), %rax
	movq %rax, %rdi
	movl $0, %eax
	call printf@PLT
	movl $0, %eax
	movl $0, %esi
	movl $0, %ecx
	movl $0, %edx
	movl $0, %r8d
	movl $0, %r9d
	movl -12(%rbp), %esi
	leaq .LP3(%rip), %rax
	movq %rax, %rdi
	movl $0, %eax
	call printf@PLT
	movl $0, %eax
	movl $0, %esi
	movl $0, %ecx
	movl $0, %edx
	movl $0, %r8d
	movl $0, %r9d
	movl -16(%rbp), %esi
	leaq .LP4(%rip), %rax
	movq %rax, %rdi
	movl $0, %eax
	call printf@PLT
	movl $0, %eax
	movl $0, %esi
	movl $0, %ecx
	movl $0, %edx
	movl $0, %r8d
	movl $0, %r9d
	movl -20(%rbp), %esi
	leaq .LP5(%rip), %rax
	movq %rax, %rdi
	movl $0, %eax
	call printf@PLT
	movl $0, %eax
	movl $0, %esi
	movl $0, %ecx
	movl $0, %edx
	movl $0, %r8d
	movl $0, %r9d
	movl -24(%rbp), %esi
	leaq .LP6(%rip), %rax
	movq %rax, %rdi
	movl $0, %eax
	call printf@PLT
	movl $0, %eax
	movl $0, %esi
	movl $0, %ecx
	movl $0, %edx
	movl $0, %r8d
	movl $0, %r9d
	mov $60, %rax
	mov $0, %rdi
	syscall

