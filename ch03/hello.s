  .globl main
  .type main, @function
main:
  .cfi_startproc
  leaq .L.str(%rip), %rdi
  xorl %eax, %eax
  call printf@plt
  movl $0, %eax
  ret
  .cfi_endproc

  .type .L.str, @object
  .section .rodata.str1.1, "aMS", @progbits, 1 
.L.str:
  .asciz "Hello World From Assembly\n"
.L.str.end:
  .size .L.str, .L.str.end-.L.str

