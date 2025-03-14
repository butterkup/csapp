
  .data
  .global data
  .type data, @object
data:
  .long 5052

  .text
  .global _Z3addIiET_S0_S0_
  .type _Z3addIiET_S0_S0_, @function
_Z3addIiET_S0_S0_:
  movl %edi, %eax
  addl %esi, %eax
  ret

  .text
  .global _Z3addImET_S0_S0_
  .type _Z3addImET_S0_S0_, @function
_Z3addImET_S0_S0_:
  movq %rdi, %rax
  addq %rsi, %rax
  ret
