section .text
	global _start
_start:
	mov rax, 1
	mov rdi, 1
	mov rsi, lsp1
	mov rdx, 5
	syscall

	mov rax, 1
	mov rdi, 1
	mov rsi, lsp2
	mov rdx, 13
	syscall

	mov rax, 1
	mov rdi, 1
	mov rsi, lsp3
	mov rdx, 3
	syscall

	mov rax, 1
	mov rdi, 1
	mov rsi, lsp4
	mov rdx, 4
	syscall

	mov rax, 1
	mov rdi, 1
	mov rsi, lsp5
	mov rdx, 5
	syscall

	mov rax, 1
	mov rdi, 1
	mov rsi, lsp6
	mov rdx, 33
	syscall

	mov rax, 60
	mov rdi, 0
	syscall



;---------------------------------------------------- PRINT NUMBER CODE ----------------------------------------------- ;
PrintNumber:
	sub rsp, 40
	mov rcx, rdi
	xor r11d, r11d
	test edi, edi
	jns .PN2
	neg rcx
	mov r11d, 1
.PN2:
	mov r8d, 1
	lea r10, [rsp+31]
	mov r9, -3689348814741910323
.PN3:
	mov rax, rcx
	mov rdi, r10
	mul r9
	mov rax, rcx
	sub rdi, r8
	shr rdx, 3
	lea rsi, [rdx+rdx*4]
	add rsi, rsi
	sub rax, rsi
	mov rsi, r8
	add r8, 1
	add eax, 48
	mov BYTE  [rdi], al
	mov rax, rcx
	mov rcx, rdx
	cmp rax, 9
	ja .PN3
	test r11d, r11d
	jne .PN4
	mov eax, 32
	sub rax, r8
.PN5:
	lea rsi, [rsp+rax]
	mov rdx, r8
	mov edi, 1
	mov rax, 1
	syscall
	add rsp, 40
	ret
.PN4:
	lea r8, [rsi+2]
	mov eax, 32
	sub rax, r8
	mov BYTE  [rsp+rax], 45
	jmp .PN5
; ---------------------------------------------------- PRINT NUMBER CODE ----------------------------------------------- ;

section .data
	lsp1 db 77,97,110,121,32
	lsp2 db 105,110,115,116,114,117,99,116,105,111,110,115,32
	lsp3 db 105,110,32
	lsp4 db 111,110,101,32
	lsp5 db 108,105,110,101,10
	lsp6 db 109,121,32,102,105,114,115,116,32,108,105,110,101,32,111,102,32,99,111,100,101,32,111,110,32,50,48,50,50,32,58,68,10
