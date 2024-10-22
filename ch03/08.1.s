  .globl main
  .type main, @function
main:
  .cfi_startproc
  leaq .L.str.3(%rip), %rdi
  xorl %eax, %eax
  call printf@plt
  pushq %rsp
  mov %rsp, %rsi
  leaq .L.str.1(%rip), %rdi
  xorl %eax, %eax
  call scanf@plt
  popq %rsi
  leaq .L.str.2(%rip), %rdi
  xorl %eax,%eax
  call printf@plt
  xorl %eax, %eax
  ret
  .cfi_endproc

  .globl cond
  .type cond, @function
cond:
  .cfi_startproc
  cmpw 0, %di
  je .L.cond.1
  cmpw (%rsi), %di
  jle .L.cond.1 
  movw %di, (%rsi)
.L.cond.1:
  nop
  ret
  .cfi_endproc

  .type .L.str.1, @object
  .section .rodata.str1.1, "aMS", @progbits, 1 
.L.str.1:
  .asciz "%d"
  .size .L.str.1, 3

  .type .L.str.2, @object
.L.str.2:
  .asciz "You entered: %d\n"
.L.str.2.end:
  .size .L.str.2, .L.str.2.end-.L.str.2


  .type .L.str.3, @object
.L.str.3:
  .asciz "Enter a number: "
.L.str.3.end:
  .size .L.str.3, .L.str.3.end-.L.str.3

