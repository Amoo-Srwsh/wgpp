.text
.section .rodata
	.globl main
	.type main, @function

	.LPNR:
		.string "%d\n"
		.text

	.LP1:
		.string "Hey men, with GNU assembly now!"
		.text

	.LP2:
		.string "Yeah man"
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

	leaq .LP1(%rip), %rax
	movq %rax, %rdi
	call puts@PLT
	movl $0, %eax

	leaq .LP1(%rip), %rax
	movq %rax, %rdi
	call puts@PLT
	movl $0, %eax

	leaq .LP1(%rip), %rax
	movq %rax, %rdi
	call puts@PLT
	movl $0, %eax

	leaq .LP1(%rip), %rax
	movq %rax, %rdi
	call puts@PLT
	movl $0, %eax

	leaq .LP1(%rip), %rax
	movq %rax, %rdi
	call puts@PLT
	movl $0, %eax

	leaq .LP2(%rip), %rax
	movq %rax, %rdi
	call puts@PLT
	movl $0, %eax

	mov $60, %rax
	mov $0, %rdi
	syscall

	popq %rbp
	ret

