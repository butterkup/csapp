	.file	"04-main.c"
	.text
	.globl	mscale
	.type	mscale, @function
mscale:
.LFB0:
	.cfi_startproc
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	.cfi_def_cfa_register 6
	movq  %rdi,  %rax
    imulq $4,    %rsi
    imulq $12,   %rdx
    addq  %rsi,  %rax
    addq  %rdx,  %rax
    .cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	mscale, .-mscale
	.section	.rodata
.LC0:
	.string	"mscale(%ld, %ld, %ld) = %ld\n"
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
	movq	$4, -24(%rbp)
	movq	$7, -16(%rbp)
	movq	$10, -8(%rbp)
	movq	-8(%rbp), %rdx
	movq	-16(%rbp), %rcx
	movq	-24(%rbp), %rax
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	mscale
	movq	%rax, %rsi
	movq	-8(%rbp), %rcx
	movq	-16(%rbp), %rdx
	movq	-24(%rbp), %rax
	movq	%rsi, %r8
	movq	%rax, %rsi
	leaq	.LC0(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1:
	.size	main, .-main
	.ident	"GCC: (GNU) 14.2.1 20240910"
	.section	.note.GNU-stack,"",@progbits
