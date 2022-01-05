.text
.section .rodata
	.globl main
	.type main, @function
	.LPNR:
		.string "%d"
		.text
	.LP1:
		.string "Hey men, with GNU assembly now!"
		.text
	.LP2:
		.string "Yeah man\n"
		.text

main:
	pushq %rbp
	movq %rsp, %rbp
	leaq .LP1(%rip), %rax
	movq %rax, %rdi
	movl $0, %eax
	call puts@PLT
	movl $0, %eax

	leaq .LP1(%rip), %rax
	movq %rax, %rdi
	movl $0, %eax
	call puts@PLT
	movl $0, %eax

	leaq .LP1(%rip), %rax
	movq %rax, %rdi
	movl $0, %eax
	call puts@PLT
	movl $0, %eax

	leaq .LP1(%rip), %rax
	movq %rax, %rdi
	movl $0, %eax
	call puts@PLT
	movl $0, %eax

	leaq .LP1(%rip), %rax
	movq %rax, %rdi
	movl $0, %eax
	call puts@PLT
	movl $0, %eax

	leaq .LP2(%rip), %rax
	movq %rax, %rdi
	movl $0, %eax
	call puts@PLT
	movl $0, %eax

	mov $60, %rax
	mov $0, %rdi
	syscall

