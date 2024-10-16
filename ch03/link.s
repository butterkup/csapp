  .globl add2
  .type add2, @function
add2:
  .cfi_startproc
  addl $2, %edi
  movl %edi, %eax
  ret
  .cfi_endproc

