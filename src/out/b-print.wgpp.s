.text
.section .rodata
	.globl main
	.type main, @function
	.LPNR:
		.string "%d"
		.text
	.LP1:
		.string "Hey men, with GNU assembly now!\n"
		.text
	.LP2:
		.string "Yeah man\n"
		.text

main:
	pushq %rbp
	movq %rsp, %rbp
	leaq .LP1(%rip), %rax
	movq %rax, %rdi
	call printf@PLT
	movl $0, %eax

	leaq .LP1(%rip), %rax
	movq %rax, %rdi
	call printf@PLT
	movl $0, %eax

	leaq .LP1(%rip), %rax
	movq %rax, %rdi
	call printf@PLT
	movl $0, %eax

	leaq .LP1(%rip), %rax
	movq %rax, %rdi
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

	mov $60, %rax
	mov $0, %rdi
	syscall

