.text
.section .rodata
	.globl main
	.type main, @function
	.LPNR:
		.string "%d\n"
		.text
	.LP1:
		.string "Making arithmetic!"
		.text
	.LP2:
		.string "The value of x variable is: %d\n"
		.text
	.LP3:
		.string "The value of y variable is: %d\n"
		.text
	.LP4:
		.string "The value of z variable is: %d\n"
		.text

main:
	pushq %rbp
	movq %rsp, %rbp
	subq $4, %rsp
	movl $74, -4(%rbp)

	subq $4, %rsp
	movl $8, -8(%rbp)

	subq $4, %rsp
	movl $1024, -12(%rbp)

	leaq .LP1(%rip), %rax
	movq %rax, %rdi
	call puts@PLT
	movl $0, %eax

	movl -4(%rbp), %esi
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
	movl -8(%rbp), %esi
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
	movl -12(%rbp), %esi
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
	mov $60, %rax
	mov $0, %rdi
	syscall

