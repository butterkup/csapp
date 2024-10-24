  .globl swap_add
  .type swap_add, @function
swap_add:
  .cfi_startproc
  movq (%rdi), %rdx
  movq (%rsi), %rax
  movq %rax, (%rdi)
  movq %rdx, (%rsi)
  addq %rdx, %rax
  ret
  .cfi_endproc

  .globl caller
  .type caller, @function
caller:
  .cfi_startproc
  pushq %rdi # x
  pushq %rsi # y
  leaq 8(%rsp), %rdi # &x
  movq %rsp, %rsi    # &y
  call swap_add  # swap and add values of x and y
  popq %rsi # y
  popq %rdi # x
  subq %rsi, %rdi # x - y
  imulq %rdi, %rax # (x + y) * (x - y)
  ret
  .cfi_endproc

