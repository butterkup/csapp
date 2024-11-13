	.type main, @function
	.global main
main:
	.cfi_startproc
	#call greet
	xorl %eax, %eax
	ret
	.cfi_endproc

	.type greet, @function
	.globl greet
greet:
	.cfi_startproc
	.rept 20
	leaq hello(%rip), %rdi
	xorl %eax, %eax
	call printf@plt
	.endr
	ret
	.cfi_endproc

	.section .rodata.str1.1, "aMS", @progbits, 1
	.type hello, @object
hello:
	.asciz "Hello from Assembly\n"
	.size hello, .-hello
