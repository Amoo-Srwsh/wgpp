.text
.section .rodata
	.globl main
	.type main, @function
	.LPNR:
		.string "%d\n"
		.text

main:
	pushq %rbp
	movq %rsp, %rbp
