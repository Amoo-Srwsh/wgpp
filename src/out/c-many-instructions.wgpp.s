.text
.section .rodata
	.globl main
	.type main, @function

	.LPNR:
		.string "%d\n"
		.text

	.LP1:
		.string "Many instructions "
		.text

	.LP2:
		.string "in on line "
		.text

	.LP3:
		.string "does it work? "
		.text

	.LP4:
		.string "Sure, it does!!"
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

	leaq .LP2(%rip), %rax
	movq %rax, %rdi
	call puts@PLT
	movl $0, %eax

	leaq .LP3(%rip), %rax
	movq %rax, %rdi
	call puts@PLT
	movl $0, %eax

	leaq .LP4(%rip), %rax
	movq %rax, %rdi
	call puts@PLT
	movl $0, %eax

	mov $60, %rax
	mov $0, %rdi
	syscall

	popq %rbp
	ret

