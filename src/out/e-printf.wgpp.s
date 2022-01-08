.text
.section .rodata
	.globl main
	.type main, @function
	.LPNR:
		.string "%d\n"
		.text
	.LP1:
		.string "%d is the value\n"
		.text
	.LP2:
		.string "%d is a value\n"
		.text
	.LP3:
		.string ""
		.text
	.LP4:
		.string "%d %d %d %d %d\n"
		.text
	.LP5:
		.string "Var: %%s %d\n"
		.text

main:
	pushq %rbp
	movq %rsp, %rbp
	subq $4, %rsp
	movl $16, -4(%rbp)

	subq $4, %rsp
	movl $17, -8(%rbp)

	subq $4, %rsp
	movl $18, -12(%rbp)

	subq $4, %rsp
	movl $19, -16(%rbp)

	subq $4, %rsp
	movl $-23, -20(%rbp)

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
	movl -16(%rbp), %esi
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
	movl -20(%rbp), %esi
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
	leaq .LP3(%rip), %rax
	movq %rax, %rdi
	call puts@PLT
	movl $0, %eax

	movl -20(%rbp), %esi
	movl -16(%rbp), %edx
	movl -12(%rbp), %ecx
	movl -8(%rbp), %r8d
	movl -4(%rbp), %r9d
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
	movl -4(%rbp), %esi
	movl -8(%rbp), %edx
	movl -12(%rbp), %ecx
	movl -16(%rbp), %r8d
	movl -20(%rbp), %r9d
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
	movl -4(%rbp), %esi
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
	mov $60, %rax
	mov $0, %rdi
	syscall

