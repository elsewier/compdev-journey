	global	main
	extern	printf
	section	.text
LC0:	db	"%d",10,0
printint:
	push	rbp
	mov	rbp, rsp
	sub	rsp, 16
	mov	[rbp-4], edi
	mov	eax, [rbp-4]
	mov	esi, eax
	lea	rdi, [rel LC0]
	mov	eax, 0
	call	printf
	nop
	leave
	ret

main:
	push	rbp
	mov	rbp, rsp
	mov	r8, 13
	mov	r9, 6
	sub	r8, r9
	mov	r9, 4
	mov	r10, 5
	imul	r10, r9
	add	r10, r8
	mov	r8, 8
	mov	r9, 3
	mov	rax, r8
	cqo
	idiv	r9
	mov	r8, rax
	add	r8, r10
	mov	rdi, r8
	call	printint
	mov	eax, 0
	pop	rbp
	ret
