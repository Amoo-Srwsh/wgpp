.text
.section .rodata
	.globl main
	.type main, @function

	.LPNR:
		.string "%d\n"
		.text

	.data
	.type .auxINT, @object
	.auxINT:
		.long 0
		.text

powM:
	cmpl %edi, %r15d
	jne powH
	ret
powH:
	imul %r13d, %edx
	incl %r15d
	jmp powM

main:
	pushq   %rbp
	movq    %rsp, %rbp

	subq $4, %rsp
	movl $4, -4(%rbp)

	subq $4, %rsp
	movl -4(%rbp), %eax
	movl %eax, -8(%rbp)

	movl -4(%rbp), %eax
	movl %eax, %esi
	leaq .LPNR(%rip), %rax
	movq %rax, %rdi
	movl $0, %eax
	call printf@PLT
	movl $0, %eax

	movl $5, %eax
	movl %eax, -4(%rbp)

	movl -4(%rbp), %eax
	movl %eax, %esi
	leaq .LPNR(%rip), %rax
	movq %rax, %rdi
	movl $0, %eax
	call printf@PLT
	movl $0, %eax

	movl -8(%rbp), %eax
	movl %eax, -4(%rbp)

	movl -4(%rbp), %eax
	movl %eax, %esi
	leaq .LPNR(%rip), %rax
	movq %rax, %rdi
	movl $0, %eax
	call printf@PLT
	movl $0, %eax

	movl $0, %eax
	movl %eax, -4(%rbp)

	movl -4(%rbp), %eax
	movl %eax, %esi
	leaq .LPNR(%rip), %rax
	movq %rax, %rdi
	movl $0, %eax
	call printf@PLT
	movl $0, %eax

	movl -4(%rbp), %r14d
	subl $4, %r14d

	movl %r14d, %eax
	movl %eax, -4(%rbp)

	movl -4(%rbp), %eax
	movl %eax, %esi
	leaq .LPNR(%rip), %rax
	movq %rax, %rdi
	movl $0, %eax
	call printf@PLT
	movl $0, %eax

	movq $60, %rax
	movq $0, %rdi
	syscall

	popq %rbp
	ret

