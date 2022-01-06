.text
.section .rodata
	.globl main
	.type main, @function
	.LPNR:
		.string "%d"
		.text
	.LP1:
		.string "\n"
		.text
	.LP2:
		.string "Code error will be: "
		.text

main:
	pushq %rbp
	movq %rsp, %rbp
	sub $4, %rsp
	movl $1, -4(%rbp)

	sub $4, %rsp
	movl $2, -8(%rbp)

	sub $4, %rsp
	movl $3, -12(%rbp)

	sub $4, %rsp
	movl $0, -16(%rbp)

	movl -4(%rbp), %eax
	mov %eax, %esi
	leaq .LPNR(%rip), %rax
	movq %rax, %rdi
	movl $0, %eax
	call printf@PLT
	movl $0, %eax

	leaq .LP1(%rip), %rax
	movq %rax, %rdi
	call printf@PLT
	movl $0, %eax

	movl -8(%rbp), %eax
	mov %eax, %esi
	leaq .LPNR(%rip), %rax
	movq %rax, %rdi
	movl $0, %eax
	call printf@PLT
	movl $0, %eax

	leaq .LP1(%rip), %rax
	movq %rax, %rdi
	call printf@PLT
	movl $0, %eax

	movl -12(%rbp), %eax
	mov %eax, %esi
	leaq .LPNR(%rip), %rax
	movq %rax, %rdi
	movl $0, %eax
	call printf@PLT
	movl $0, %eax

	leaq .LP1(%rip), %rax
	movq %rax, %rdi
	call printf@PLT
	movl $0, %eax

	leaq .LP2(%rip), %rax
	movq %rax, %rdi
	call printf@PLT
	movl $0, %eax

	movl -16(%rbp), %eax
	mov %eax, %esi
	leaq .LPNR(%rip), %rax
	movq %rax, %rdi
	movl $0, %eax
	call printf@PLT
	movl $0, %eax

	leaq .LP1(%rip), %rax
	movq %rax, %rdi
	call printf@PLT
	movl $0, %eax

	mov $60, %rax
	mov -16(%rbp), %rdi
	syscall

