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

	.LP1:
		.string "X: %d\n"
		.text

	.LP2:
		.string "Y: %d\n"
		.text

	.LP3:
		.string "Z: %d\n"
		.text

	.LP4:
		.string "ZYX: %d\n"
		.text

	.LP5:
		.string "Random (mod operation):"
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

	movl -4(%rbp), %r14d
	imull $2, %r14d

	subq $4, %rsp
	movl %r14d, -8(%rbp)

	movl -8(%rbp), %r14d
	movl $0, %edx
	movl %r14d, %eax
	movl -4(%rbp), %ecx
	divl %ecx
	movl %eax, %r14d

	subq $4, %rsp
	movl %r14d, -12(%rbp)

	movl -4(%rbp), %r14d
	subl -8(%rbp), %r14d
	subl -12(%rbp), %r14d

	subq $4, %rsp
	movl %r14d, -16(%rbp)

	movl -4(%rbp), %esi
	leaq .LP1(%rip), %rax
	movq %rax, %rdi
	movl $0, %eax
	call printf@PLT
	movl $0, %eax

	movl $0, %esi

	movl -8(%rbp), %esi
	leaq .LP2(%rip), %rax
	movq %rax, %rdi
	movl $0, %eax
	call printf@PLT
	movl $0, %eax

	movl $0, %esi

	movl -12(%rbp), %esi
	leaq .LP3(%rip), %rax
	movq %rax, %rdi
	movl $0, %eax
	call printf@PLT
	movl $0, %eax

	movl $0, %esi

	movl -16(%rbp), %esi
	leaq .LP4(%rip), %rax
	movq %rax, %rdi
	movl $0, %eax
	call printf@PLT
	movl $0, %eax

	movl $0, %esi

	leaq .LP5(%rip), %rax
	movq %rax, %rdi
	call puts@PLT
	movl $0, %eax

	movl -4(%rbp), %r14d
	movl $0, %edx
	movl %r14d, %eax
	movl $2, %ecx
	divl %ecx
	movl %edx, %r14d

	movl %r14d, %eax
	movl %eax, %esi
	leaq .LPNR(%rip), %rax
	movq %rax, %rdi
	movl $0, %eax
	call printf@PLT
	movl $0, %eax

	movl -16(%rbp), %r14d
	imull $-1, %r14d

	movl %r14d, .auxINT(%rip)
	movq $60, %rax
	movq .auxINT(%rip), %rdi
	syscall
	movl $0, .auxINT(%rip)

	popq %rbp
	ret

