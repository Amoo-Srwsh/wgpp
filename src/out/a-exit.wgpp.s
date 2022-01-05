.text
.section .rodata
	.globl main
	.type main, @function
	.LPNR:
		.string "%d"
		.text


main:
	pushq %rbp
	movq %rsp, %rbp
	mov $60, %rax
	mov $16, %rdi
	syscall

	mov $60, %rax
	mov $-3, %rdi
	syscall

