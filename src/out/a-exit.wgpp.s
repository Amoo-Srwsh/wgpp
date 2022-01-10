.text
.section .rodata
	.globl main
	.type main, @function

	.LPNR:
		.string "%d\n"
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

	mov $60, %rax
	mov $16, %rdi
	syscall

	popq %rbp
	ret

