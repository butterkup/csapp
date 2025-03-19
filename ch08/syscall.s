  .text
  .global main
  .type main, @function
main:
  xorq %rax, %rax
  mov $1, %rdi # print to stdout
  leaq text(%rip), %rsi # the null terminated string to be printed
  mov $textlen, %rdx # length of the string
  mov $1, %rax # the write syscall code
  # call write with passed arguments
  syscall
  xorq %rax, %rax

  # Print the prompt string
  mov $2, %rdi
  leaq prompt(%rip), %rsi
  mov $promptlen, %rdx
  mov $1, %rax
  syscall

  push %rbp
  push %rbx
  # Get user name
  mov $0, %rdi
  mov %rsp, %rbp
  subq $30, %rsp
  mov %rbp, %rsi
  mov $30, %rdx
  mov $0, %rax
  syscall

  testq %rax, %rax
  jle read_name_error
  mov %rax, %rbx
  # Remove linefeed character at the end
  decq %rbx

  # Greet the user
  mov $1, %rdi
  leaq heyf(%rip), %rsi
  mov $heyflen, %rdx
  mov $1, %rax
  syscall

  mov $1, %rdi
  mov %rbp, %rsi
  mov %rbx, %rdx
  mov $1, %rax
  syscall

  mov $1, %rdi
  leaq askf(%rip), %rsi
  mov $askflen, %rdx
  mov $1, %rax
  syscall

  mov $0, %rax
  jmp went_well

read_name_error:
  mov $1, %rdi
  leaq readerrorf(%rip), %rsi
  mov $readerrorflen, %rdx
  mov $1, %rax
  syscall
  mov $1, %rax

went_well:
  addq $30, %rsp
  pop %rbx
  pop %rbp
  ret

  .global text
  .section .rodata
  .type text, @object
text:
  .ascii "Hello from ASM printed using the write syscall!\n" 
  .equ textlen, .-text

  .global prompt
  .section .rodata
  .type prompt, @object
prompt:
  .ascii "Enter your name: " 
  .equ promptlen, .-prompt

  .global heyf
  .section .rodata
  .type heyf, @object
heyf:
  .ascii "Hello "
  .equ heyflen, .-heyf

  .section .rodata
  .global readerrorf
  .type readerrorf, @object
readerrorf:
  .ascii "\033[31mError reading name!!!\033[0m\n" 
  .equ readerrorflen, .-readerrorf

  .global askf
  .section .rodata
  .type askf, @object
askf:
  .ascii ", how was your day?\n" 
  .equ askflen, .-askf

