  .globl main
  .type main, @function
main:
  .cfi_startproc
  leaq people(%rip), %rdi
  movq $4, %rsi
  call greet_people
.main.greet.loop:
  call getngreet
  movq stdin(%rip), %rdi
  call feof@plt
  testq %rax, %rax
  je .main.greet.loop
  xorl %eax, %eax
  ret
  .cfi_endproc

  .globl greet_people
  .type greet_people, @function
greet_people:
  .cfi_startproc
  cmpq $0, %rsi
  je .greet_people.return
  pushq %rdi
  pushq %rsi
.greet_people.loop:
  movq 8(%rsp), %rdi
  call greet_person
  addq $12, 8(%rsp)
  decq (%rsp)
  jg .greet_people.loop
  addq $16, %rsp
.greet_people.return:
  nop
  ret
  .cfi_endproc

  .globl getngreet
  .type getngreet, @function
getngreet:
  .cfi_startproc
  movq stderr(%rip), %rdi
  leaq .getngreet.printfmt(%rip), %rsi
  xorl %eax, %eax
  call fprintf@plt
  subq $32, %rsp
  leaq 12(%rsp), %rsi
  leaq 8(%rsp), %rdx
  leaq .getngreet.scanfmt(%rip), %rdi
  call scanf@plt
  testq %rax, %rax
  jne .getngreet.scan_success
  leaq .getngreet.scan_fail.name(%rip), %rax
  movq %rax, (%rsp)
  movl $-1, 8(%rsp)
  jmp .getngreet.scan_failure
.getngreet.scan_success:
  leaq 12(%rsp), %rax
  movq %rax, (%rsp)
  movq %rsp, %rdi
.getngreet.scan_failure:
  call greet_person
  addq $32, %rsp
  ret
  .cfi_endproc

  .globl greet_person
  .type greet_person, @function
greet_person:
  .cfi_startproc
  movq (%rdi), %rsi
  movl 8(%rdi), %edx
  leaq .greet_person.template(%rip), %rdi
  xorl %eax, %eax
  call printf@plt
  ret
  .cfi_endproc

  .data
  .type people, @object
people:
  .quad .people.1.name
  .long 22
  .quad .people.2.name
  .long 11
  .quad .people.3.name
  .long 39
  .quad .people.4.name
  .long 16
  .size people, .-people

  .section .rodata.str1.1, "aMS", @progbits, 1 
  .type .getngreet.printfmt, @object
.getngreet.printfmt:
  .asciz "Enter Name and Age: "
  .size .getngreet.printfmt, .-.getngreet.printfmt

  .type .getngreet.scan_fail.name, @object
.getngreet.scan_fail.name:
  .asciz "<Error Getting Name>"
  .size .getngreet.scan_fail.name, .-.getngreet.scan_fail.name

  .type .getngreet.scanfmt, @object
.getngreet.scanfmt:
  .asciz "%11s %d"
  .size .getngreet.scanfmt, .-.getngreet.scanfmt

  .type .people.1.name, @object
.people.1.name:
  .asciz "Simon Nganga"
  .size .people.1.name,.-.people.1.name

  .type .people.2.name, @object
.people.2.name:
  .asciz "Faith Njeri"
  .size .people.2.name,.-.people.2.name

  .type .people.3.name, @object
.people.3.name:
  .asciz "Lydia Wanjiru"
  .size .people.3.name,.-.people.3.name

  .type .people.4.name, @object
.people.4.name:
  .asciz "John Doe"
  .size .people.4.name, .-.people.4.name

  .type .greet_person.template, @object
.greet_person.template:
  .asciz "Hello %s, you are %d years old!\n"
  .size .greet_person.template, .-.greet_person.template
