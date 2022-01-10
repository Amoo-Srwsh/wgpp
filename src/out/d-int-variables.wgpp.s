.text
.section .rodata
	.globl main
	.type main, @function

	.LPNR:
		.string "%d\n"
		.text

	.LP1:
		.string "Code error will be:"
		.text

powM:
	cmp %edi, %r15d
	jne powH
	ret
powH:
	imul %r13d, %edx
	inc %r15d
	jmp powM

main:
	pushq   %rbp
	movq    %rsp, %rbp

	subq $4, %rsp
	movl $1, -4(%rbp)

	subq $4, %rsp
	movl $2, -8(%rbp)

	subq $4, %rsp
	movl $-3, -12(%rbp)

	subq $4, %rsp
	movl $-4, -16(%rbp)

	subq $4, %rsp
	movl $16, -20(%rbp)

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

	leaq .LP1(%rip), %rax
	movq %rax, %rdi
	call puts@PLT
	movl $0, %eax

	movl -20(%rbp), %eax
	movl %eax, %esi
	leaq .LPNR(%rip), %rax
	movq %rax, %rdi
	movl $0, %eax
	call printf@PLT
	movl $0, %eax

	mov $60, %rax
	mov -20(%rbp), %rdi
	syscall

	popq %rbp
	ret

