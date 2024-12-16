	.text
	.file	"twindle.c"
	.globl	twindle1                        # -- Begin function twindle1
	.p2align	4, 0x90
	.type	twindle1,@function
twindle1:                               # @twindle1
	.cfi_startproc
# %bb.0:
	movq	(%rsi), %rax
	addq	%rax, %rax
	addq	%rax, (%rdi)
	retq
.Lfunc_end0:
	.size	twindle1, .Lfunc_end0-twindle1
	.cfi_endproc
                                        # -- End function
	.globl	twindle2                        # -- Begin function twindle2
	.p2align	4, 0x90
	.type	twindle2,@function
twindle2:                               # @twindle2
	.cfi_startproc
# %bb.0:
	movq	(%rsi), %rax
	addq	%rax, %rax
	addq	%rax, (%rdi)
	retq
.Lfunc_end1:
	.size	twindle2, .Lfunc_end1-twindle2
	.cfi_endproc
                                        # -- End function
	.globl	swap                            # -- Begin function swap
	.p2align	4, 0x90
	.type	swap,@function
swap:                                   # @swap
	.cfi_startproc
# %bb.0:
	movq	(%rdi), %rax
	movq	(%rsi), %rcx
	leaq	(%rcx,%rax), %rdx
	movq	%rdx, (%rdi)
	movq	%rax, (%rsi)
	movq	%rcx, (%rdi)
	retq
.Lfunc_end2:
	.size	swap, .Lfunc_end2-swap
	.cfi_endproc
                                        # -- End function
	.globl	f                               # -- Begin function f
	.p2align	4, 0x90
	.type	f,@function
f:                                      # @f
	.cfi_startproc
# %bb.0:
	movl	$50, %eax
	retq
.Lfunc_end3:
	.size	f, .Lfunc_end3-f
	.cfi_endproc
                                        # -- End function
	.globl	summer                          # -- Begin function summer
	.p2align	4, 0x90
	.type	summer,@function
summer:                                 # @summer
	.cfi_startproc
# %bb.0:
	movl	$200, %eax
	retq
.Lfunc_end4:
	.size	summer, .Lfunc_end4-summer
	.cfi_endproc
                                        # -- End function
	.globl	by4                             # -- Begin function by4
	.p2align	4, 0x90
	.type	by4,@function
by4:                                    # @by4
	.cfi_startproc
# %bb.0:
	movl	$200, %eax
	retq
.Lfunc_end5:
	.size	by4, .Lfunc_end5-by4
	.cfi_endproc
                                        # -- End function
	.globl	main                            # -- Begin function main
	.p2align	4, 0x90
	.type	main,@function
main:                                   # @main
	.cfi_startproc
# %bb.0:
	movl	$400, %eax                      # imm = 0x190
	retq
.Lfunc_end6:
	.size	main, .Lfunc_end6-main
	.cfi_endproc
                                        # -- End function
	.type	.L.str,@object                  # @.str
	.section	.rodata.str1.1,"aMS",@progbits,1
.L.str:
	.asciz	"Simon"
	.size	.L.str, 6

	.type	value,@object                   # @value
	.data
	.globl	value
	.p2align	3, 0x0
value:
	.quad	.L.str
	.size	value, 8

	.type	.L.str.1,@object                # @.str.1
	.section	.rodata.str1.1,"aMS",@progbits,1
.L.str.1:
	.asciz	"Nganga"
	.size	.L.str.1, 7

	.type	name,@object                    # @name
	.data
	.globl	name
	.p2align	3, 0x0
name:
	.quad	.L.str.1
	.size	name, 8

	.ident	"clang version 19.1.7"
	.section	".note.GNU-stack","",@progbits
	.addrsig
