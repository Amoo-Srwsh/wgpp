.text
.section .rodata
	.globl main
	.type main, @function
	.LPNR:
		.string "%d\n"
		.text

main:
	pushq %rbp
	movq %rsp, %rbp
	subq $4, %rsp
	movl $16, -4(%rbp)

	subq $4, %rsp
	movl -4(%rbp), %eax
	movl %eax, -8(%rbp)
	movl $0, %eax
	subq $4, %rsp
	movl -8(%rbp), %eax
	movl %eax, -12(%rbp)
	movl $0, %eax
	subq $4, %rsp
	movl -12(%rbp), %eax
	movl %eax, -16(%rbp)
	movl $0, %eax
	subq $4, %rsp
	movl -16(%rbp), %eax
	movl %eax, -20(%rbp)
	movl $0, %eax
	subq $4, %rsp
	movl -20(%rbp), %eax
	movl %eax, -24(%rbp)
	movl $0, %eax
	subq $4, %rsp
	movl -24(%rbp), %eax
	movl %eax, -28(%rbp)
	movl $0, %eax
	movl -4(%rbp), %eax
	movl %eax, %esi
	leaq .LPNR(%rip), %rax
	movq %rax, %rdi
	movl $0, %eax
	call printf@PLT
	movl $0, %eax

	movl -8(%rbp), %eax
	movl %eax, %esi
	leaq .LPNR(%rip), %rax
	movq %rax, %rdi
	movl $0, %eax
	call printf@PLT
	movl $0, %eax

	movl -12(%rbp), %eax
	movl %eax, %esi
	leaq .LPNR(%rip), %rax
	movq %rax, %rdi
	movl $0, %eax
	call printf@PLT
	movl $0, %eax

	movl -16(%rbp), %eax
	movl %eax, %esi
	leaq .LPNR(%rip), %rax
	movq %rax, %rdi
	movl $0, %eax
	call printf@PLT
	movl $0, %eax

	movl -20(%rbp), %eax
	movl %eax, %esi
	leaq .LPNR(%rip), %rax
	movq %rax, %rdi
	movl $0, %eax
	call printf@PLT
	movl $0, %eax

	movl -24(%rbp), %eax
	movl %eax, %esi
	leaq .LPNR(%rip), %rax
	movq %rax, %rdi
	movl $0, %eax
	call printf@PLT
	movl $0, %eax

	movl -28(%rbp), %eax
	movl %eax, %esi
	leaq .LPNR(%rip), %rax
	movq %rax, %rdi
	movl $0, %eax
	call printf@PLT
	movl $0, %eax

	mov $60, %rax
	mov $0, %rdi
	syscall
