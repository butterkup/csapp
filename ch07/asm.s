
  .text
  .global main
  .type main, @function
main:
  leaq string(%rip), %rdi
  movl data(%rip), %esi
  xorl %eax, %eax
  call printf
  xorl %eax, %eax
  ret

  .section .rodata
  .type string, @object
string:
  .asciz "data = %d\n"

