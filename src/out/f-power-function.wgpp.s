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
		.string "-------------------------"
		.text

# ------------------------------------------- POWER OPERATION -------------------------------------------
powM:
	cmpl $0, %edi
	je powE_by_0
	cmpl $-1, %edi
	jle powE_by_SN
	cmpl %edi, %r15d
	jne powH
	ret
powH:
	imul %r13d, %edx
	incl %r15d
	jmp powM
powE_by_0:
	movl $1, %edx
	ret
powE_by_SN:
	cmpl $-1, %edx
	je powE_by_Sone
	cmpl $1, %edx
	je powE_by_USone
	movl $0, %edx
	ret
powE_by_Sone:
	movl $-1, %edx
	ret
powE_by_USone:
	movl $1, %edx
	ret
return_help:
	ret
check_pwer_abs:
	cmpl $1, %edx
	jge return_help
	negl %r13d
	ret
# ------------------------------------------- POWER OPERATION -------------------------------------------
main:
	pushq   %rbp
	movq    %rsp, %rbp

	subq $4, %rsp
	movl $4, -4(%rbp)

	movl -4(%rbp), %r14d
	imull $-1, %r14d

	subq $4, %rsp
	movl %r14d, -8(%rbp)

	subq $4, %rsp
	movl $-1, -12(%rbp)

	movl -4(%rbp), %r14d
	movl %r14d, %edx
	movl %r14d, %r13d
	movl -4(%rbp), %edi
	movl $1, %r15d
	call check_pwer_abs
	call powM
	movl %edx, %r14d

	movl %r14d, %eax
	movl %eax, %esi
	leaq .LPNR(%rip), %rax
	movq %rax, %rdi
	movl $0, %eax
	call printf@PLT
	movl $0, %eax

	movl -4(%rbp), %r14d
	movl %r14d, %edx
	movl %r14d, %r13d
	movl $-1, %edi
	movl $1, %r15d
	call check_pwer_abs
	call powM
	movl %edx, %r14d

	movl %r14d, %eax
	movl %eax, %esi
	leaq .LPNR(%rip), %rax
	movq %rax, %rdi
	movl $0, %eax
	call printf@PLT
	movl $0, %eax

	movl -8(%rbp), %r14d
	movl %r14d, %edx
	movl %r14d, %r13d
	movl $3, %edi
	movl $1, %r15d
	call check_pwer_abs
	call powM
	movl %edx, %r14d

	movl %r14d, %eax
	movl %eax, %esi
	leaq .LPNR(%rip), %rax
	movq %rax, %rdi
	movl $0, %eax
	call printf@PLT
	movl $0, %eax

	movl -12(%rbp), %r14d
	movl %r14d, %edx
	movl %r14d, %r13d
	movl -12(%rbp), %edi
	movl $1, %r15d
	call check_pwer_abs
	call powM
	movl %edx, %r14d

	movl %r14d, %eax
	movl %eax, %esi
	leaq .LPNR(%rip), %rax
	movq %rax, %rdi
	movl $0, %eax
	call printf@PLT
	movl $0, %eax

	movl -12(%rbp), %r14d
	movl %r14d, %edx
	movl %r14d, %r13d
	movl $0, %edi
	movl $1, %r15d
	call check_pwer_abs
	call powM
	movl %edx, %r14d

	movl %r14d, %eax
	movl %eax, %esi
	leaq .LPNR(%rip), %rax
	movq %rax, %rdi
	movl $0, %eax
	call printf@PLT
	movl $0, %eax

	movl -12(%rbp), %r14d
	movl %r14d, %edx
	movl %r14d, %r13d
	movl $-34, %edi
	movl $1, %r15d
	call check_pwer_abs
	call powM
	movl %edx, %r14d

	movl %r14d, %eax
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

	movl $-1, %eax
	movl %eax, %esi
	leaq .LPNR(%rip), %rax
	movq %rax, %rdi
	movl $0, %eax
	call printf@PLT
	movl $0, %eax

	movl $1, %eax
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

