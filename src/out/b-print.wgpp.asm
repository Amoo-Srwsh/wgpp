section .text
	global _start
_start:
	mov rax, 1
	mov rdi, 1
	mov rsi, lsp1
	mov rdx, 9
	syscall

	mov rax, 1
	mov rdi, 1
	mov rsi, lsp2
	mov rdx, 12
	syscall

	mov rax, 1
	mov rdi, 1
	mov rsi, lsp3
	mov rdx, 11
	syscall

	mov rax, 1
	mov rdi, 1
	mov rsi, lsp4
	mov rdx, 8
	syscall

	mov rax, 1
	mov rdi, 1
	mov rsi, lsp5
	mov rdx, 8
	syscall

	mov rax, 1
	mov rdi, 1
	mov rsi, lsp6
	mov rdx, 8
	syscall

	mov rax, 1
	mov rdi, 1
	mov rsi, lsp7
	mov rdx, 8
	syscall

	mov rax, 1
	mov rdi, 1
	mov rsi, lsp8
	mov rdx, 8
	syscall

	mov rax, 1
	mov rdi, 1
	mov rsi, lsp9
	mov rdx, 8
	syscall

	mov rax, 1
	mov rdi, 1
	mov rsi, lsp10
	mov rdx, 8
	syscall

	mov rax, 1
	mov rdi, 1
	mov rsi, lsp11
	mov rdx, 8
	syscall

	mov rax, 1
	mov rdi, 1
	mov rsi, lsp12
	mov rdx, 8
	syscall

	mov rax, 1
	mov rdi, 1
	mov rsi, lsp13
	mov rdx, 8
	syscall

	mov rax, 1
	mov rdi, 1
	mov rsi, lsp14
	mov rdx, 8
	syscall

	mov rax, 1
	mov rdi, 1
	mov rsi, lsp15
	mov rdx, 8
	syscall

	mov rax, 1
	mov rdi, 1
	mov rsi, lsp16
	mov rdx, 8
	syscall

	mov rax, 1
	mov rdi, 1
	mov rsi, lsp17
	mov rdx, 8
	syscall

	mov rax, 1
	mov rdi, 1
	mov rsi, lsp18
	mov rdx, 8
	syscall

	mov rax, 1
	mov rdi, 1
	mov rsi, lsp19
	mov rdx, 8
	syscall

	mov rax, 1
	mov rdi, 1
	mov rsi, lsp20
	mov rdx, 8
	syscall

	mov rax, 1
	mov rdi, 1
	mov rsi, lsp21
	mov rdx, 8
	syscall

	mov rax, 1
	mov rdi, 1
	mov rsi, lsp22
	mov rdx, 8
	syscall

	mov rax, 1
	mov rdi, 1
	mov rsi, lsp23
	mov rdx, 8
	syscall

	mov rax, 1
	mov rdi, 1
	mov rsi, lsp24
	mov rdx, 8
	syscall

	mov rax, 1
	mov rdi, 1
	mov rsi, lsp25
	mov rdx, 8
	syscall

	mov rax, 1
	mov rdi, 1
	mov rsi, lsp26
	mov rdx, 8
	syscall

	mov rax, 1
	mov rdi, 1
	mov rsi, lsp27
	mov rdx, 8
	syscall

	mov rax, 1
	mov rdi, 1
	mov rsi, lsp28
	mov rdx, 8
	syscall

	mov rax, 1
	mov rdi, 1
	mov rsi, lsp29
	mov rdx, 8
	syscall

	mov rax, 1
	mov rdi, 1
	mov rsi, lsp30
	mov rdx, 8
	syscall

	mov rax, 1
	mov rdi, 1
	mov rsi, lsp31
	mov rdx, 8
	syscall

	mov rax, 1
	mov rdi, 1
	mov rsi, lsp32
	mov rdx, 8
	syscall

	mov rax, 1
	mov rdi, 1
	mov rsi, lsp33
	mov rdx, 8
	syscall

	mov rax, 1
	mov rdi, 1
	mov rsi, lsp34
	mov rdx, 8
	syscall

	mov rax, 1
	mov rdi, 1
	mov rsi, lsp35
	mov rdx, 8
	syscall

	mov rax, 1
	mov rdi, 1
	mov rsi, lsp36
	mov rdx, 8
	syscall

	mov rax, 1
	mov rdi, 1
	mov rsi, lsp37
	mov rdx, 8
	syscall

	mov rax, 1
	mov rdi, 1
	mov rsi, lsp38
	mov rdx, 8
	syscall

	mov rax, 1
	mov rdi, 1
	mov rsi, lsp39
	mov rdx, 8
	syscall

	mov rax, 1
	mov rdi, 1
	mov rsi, lsp40
	mov rdx, 1
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
	lsp1 db 72,101,121,44,32,109,101,110,10
	lsp2 db 73,116,32,119,111,114,107,115,33,33,33,10
	lsp3 db 51,49,45,49,50,45,50,48,50,49,10
	lsp4 db 9,45,32,106,100,112,109,109
	lsp5 db 9,45,32,106,100,112,109,109
	lsp6 db 9,45,32,106,100,112,109,109
	lsp7 db 9,45,32,106,100,112,109,109
	lsp8 db 9,45,32,106,100,112,109,109
	lsp9 db 9,45,32,106,100,112,109,109
	lsp10 db 9,45,32,106,100,112,109,109
	lsp11 db 9,45,32,106,100,112,109,109
	lsp12 db 9,45,32,106,100,112,109,109
	lsp13 db 9,45,32,106,100,112,109,109
	lsp14 db 9,45,32,106,100,112,109,109
	lsp15 db 9,45,32,106,100,112,109,109
	lsp16 db 9,45,32,106,100,112,109,109
	lsp17 db 9,45,32,106,100,112,109,109
	lsp18 db 9,45,32,106,100,112,109,109
	lsp19 db 9,45,32,106,100,112,109,109
	lsp20 db 9,45,32,106,100,112,109,109
	lsp21 db 9,45,32,106,100,112,109,109
	lsp22 db 9,45,32,106,100,112,109,109
	lsp23 db 9,45,32,106,100,112,109,109
	lsp24 db 9,45,32,106,100,112,109,109
	lsp25 db 9,45,32,106,100,112,109,109
	lsp26 db 9,45,32,106,100,112,109,109
	lsp27 db 9,45,32,106,100,112,109,109
	lsp28 db 9,45,32,106,100,112,109,109
	lsp29 db 9,45,32,106,100,112,109,109
	lsp30 db 9,45,32,106,100,112,109,109
	lsp31 db 9,45,32,106,100,112,109,109
	lsp32 db 9,45,32,106,100,112,109,109
	lsp33 db 9,45,32,106,100,112,109,109
	lsp34 db 9,45,32,106,100,112,109,109
	lsp35 db 9,45,32,106,100,112,109,109
	lsp36 db 9,45,32,106,100,112,109,109
	lsp37 db 9,45,32,106,100,112,109,109
	lsp38 db 9,45,32,106,100,112,109,109
	lsp39 db 9,45,32,106,100,112,109,109
	lsp40 db 10
