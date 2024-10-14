	.file	"05-main.c"
	.text
	.globl	mult
	.type	mult, @function
mult:
.LFB0:
	.cfi_startproc
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	.cfi_def_cfa_register 6
	.cfi_def_cfa 7, 8
	movq (%rdi), %rax
    imulq 8(%rdi)
    movq %rdx, (%rdi)
    movq %rax, 8(%rdi)
    ret
	.cfi_endproc
.LFE0:
	.size	mult, .-mult
	.section	.rodata
.LC1:
	.string	"%ld * %ld = "
.LC2:
	.string	"[%ld_%ld, %ld] -> %.10llf\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB1:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movl	%edi, -36(%rbp)
	movq	%rsi, -48(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movabsq	$1153203048319815681, %rax
	movq	%rax, -32(%rbp)
	movabsq	$4294967296, %rax
	movq	%rax, -24(%rbp)
	movq	-24(%rbp), %rdx
	movq	-32(%rbp), %rax
	movq	%rax, %rsi
	leaq	.LC1(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	leaq	-32(%rbp), %rax
	movq	%rax, %rdi
	call	mult
	fldt	-32(%rbp)
	fldt	-32(%rbp)
	movq	-24(%rbp), %rdx
	movq	-32(%rbp), %rax
	leaq	-16(%rsp), %rsp
	fstpt	(%rsp)
	leaq	-16(%rsp), %rsp
	fstpt	(%rsp)
	movq	%rax, %rsi
	leaq	.LC2(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	addq	$32, %rsp
	movl	$0, %eax
	movq	-8(%rbp), %rdx
	subq	%fs:40, %rdx
	je	.L4
	call	__stack_chk_fail@PLT
.L4:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1:
	.size	main, .-main
	.ident	"GCC: (GNU) 14.2.1 20240910"
	.section	.note.GNU-stack,"",@progbits
