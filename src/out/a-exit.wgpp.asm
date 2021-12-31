section .text
	global _start
_start:
	mov rax, 60
	mov rdi, 345
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
