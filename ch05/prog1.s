	.file	"prog1.c"
	.text
	.p2align 4
	.globl	vec_rec_init
	.type	vec_rec_init, @function
vec_rec_init:
	pushq	%rbp
	movq	%rdi, %rbp
	movl	$16, %edi
	pushq	%rbx
	subq	$8, %rsp
	call	malloc@PLT
	testq	%rax, %rax
	je	.L2
	movq	%rbp, (%rax)
	movq	%rax, %rbx
	testq	%rbp, %rbp
	jg	.L12
	movq	$0, 8(%rax)
.L1:
	addq	$8, %rsp
	movq	%rbx, %rax
	popq	%rbx
	popq	%rbp
	ret
	.p2align 4,,10
	.p2align 3
.L12:
	movl	$8, %esi
	movq	%rbp, %rdi
	call	calloc@PLT
	testq	%rax, %rax
	je	.L13
	movq	%rax, 8(%rbx)
	addq	$8, %rsp
	movq	%rbx, %rax
	popq	%rbx
	popq	%rbp
	ret
.L13:
	movq	%rbx, %rdi
	call	free@PLT
.L2:
	xorl	%ebx, %ebx
	jmp	.L1
	.size	vec_rec_init, .-vec_rec_init
	.p2align 4
	.globl	vec_rec_get
	.type	vec_rec_get, @function
vec_rec_get:
	xorl	%eax, %eax
	testq	%rsi, %rsi
	js	.L14
	cmpq	%rsi, (%rdi)
	jle	.L14
	movq	8(%rdi), %rax
	movq	(%rax,%rsi,8), %rax
	movq	%rax, (%rdx)
	movl	$1, %eax
.L14:
	ret
	.size	vec_rec_get, .-vec_rec_get
	.p2align 4
	.globl	vec_rec_len
	.type	vec_rec_len, @function
vec_rec_len:
	movq	(%rdi), %rax
	ret
	.size	vec_rec_len, .-vec_rec_len
	.p2align 4
	.globl	combine1
	.type	combine1, @function
combine1:
	movq	$0, (%rsi)
	cmpq	$0, (%rdi)
	jle	.L19
	movq	8(%rdi), %rcx
	xorl	%edx, %edx
	xorl	%eax, %eax
	.p2align 4
	.p2align 4
	.p2align 3
.L21:
	addq	(%rcx,%rax,8), %rdx
	addq	$1, %rax
	movq	%rdx, (%rsi)
	cmpq	(%rdi), %rax
	jl	.L21
.L19:
	ret
	.size	combine1, .-combine1
	.ident	"GCC: (GNU) 14.2.1 20250128"
	.section	.note.GNU-stack,"",@progbits
