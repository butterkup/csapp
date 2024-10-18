  .globl call_function
  .type call_function, @function 
call_function:
  movq %rdi, %rax
  movq %rsi, %rdi
  movq %rdx, %rsi
  jmp *%rax # TAIL CALL PASSED FUNCTION 

  .globl exec_bundle
  .type exec_bundle, @function
exec_bundle:
  .cfi_startproc
  movq %rdi, %rcx
  movl 8(%rcx), %edi
  movl 12(%rcx), %esi
  movl 16(%rcx), %edx
  pushq %rcx
  call *(%rcx)
  popq %rdi
  movl %eax, 20(%rdi)
  ret
  .cfi_endproc

  .globl test_func
  .type test_func, @function
test_func:
  .cfi_startproc
  movl $5052, %eax
  ret
  .cfi_endproc

  .globl greet_people
  .type greet_people, @function
greet_people:
  .cfi_startproc
  pushq %rdi
  pushq %rsi
.Loop.greet_people.1.start:
  cmpq $0, (%rsp)
  je .Loop.greet_people.1.end
  movq 8(%rsp), %rsi
  movq (%rsi), %rdx
  movq (%rsp), %rsi
  leaq .L.my.str.2(%rip), %rdi
  xorl %eax, %eax
  call printf@plt
  addq $8, 8(%rsp)
  decq (%rsp)
  jmp .Loop.greet_people.1.start
.Loop.greet_people.1.end:
  popq %rax
  popq %rax
  ret
  .cfi_endproc

  .globl helloTn
  .type helloTn, @function
helloTn:
  .cfi_startproc
  pushq %rdi
  pushq %rsi
.Loop.helloTn.1.start:
  cmpq $0, (%rsp)
  jle .Loop.helloTn.1.end
  movq (%rsp), %rsi
  movq 8(%rsp), %rdx
  leaq .L.my.str.2(%rip), %rdi
  xorl %eax, %eax
  call printf@plt
  decq (%rsp)
  jmp .Loop.helloTn.1.start
.Loop.helloTn.1.end:
  popq %rdi
  popq %rdi
  ret
  .cfi_endproc

  .globl multiply
  .type multiply, @function 
multiply:
  .cfi_startproc
  movl %edi, %ecx
  imull %esi, %ecx
  pushq %rcx
  movl %esi, %edx
  movl %edi, %esi
  leaq .L.my.str.1(%rip), %rdi
  call printf@plt
  popq %rax
  ret
  .cfi_endproc

  .type .L.my.str.1, @object
  .section .rodata.str1.1, "aMS", @progbits, 1 
.L.my.str.1:
  .ascii "%d * %d = %d\n\0"
.L.my.str.1.end:
  .size .L.my.str.1, .L.my.str.1.end-.L.my.str.1

  .type .L.my.str.2, @object
.L.my.str.2:
  .ascii "%2d: Hello %s, how was your day?\n\0"
.L.my.str.2.end:
  .size .L.my.str.2, .L.my.str.2.end-.L.my.str.2

