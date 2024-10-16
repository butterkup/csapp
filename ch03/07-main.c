#include <stdio.h>
#include <string.h>

struct [[packed]] person {
  char name[16]; // 16 bytes
  int age; //        4 bytes
}; //               20 bytes

extern void age_state(struct person *);
extern void can_vote(struct person *);
extern void say_name(struct person *);

asm(
"  .globl age_state\n"
"  .type age_state, @function\n"
"age_state:\n"
"  .cfi_startproc\n"
"  movq %rdi, %rsi\n"
"  movl 16(%rdi), %edx\n"
"  leaq .L.my.str(%rip), %rdi\n"
"  #xorl  %eax, %eax\n"
"  movq $0, %rax\n"
"  call printf@plt\n"
"  ret\n"
"  .cfi_endproc\n"
"\n"
"  .globl can_vote\n"
"  .type can_vote, @function\n"
"can_vote:\n"
"  .cfi_startproc\n"
"  movq %rdi, %rsi\n"
"  movl 0x10(%rdi), %edx\n"
"  #subl $0x12, 16(%rdi)\n"
"  cmpl $0x12, 16(%rdi)\n"
"  jge .L.my.can_vote.voter\n"
"  leaq .L.my.str.cannot_vote(%rip), %rdi\n"
"  jmp .L.my.can_vote.show\n"
".L.my.can_vote.voter:\n"
"  leaq .L.my.str.can_vote(%rip), %rdi\n"
".L.my.can_vote.show:\n"
"  xorl %eax, %eax\n"
"  call printf@plt\n"
"  ret\n"
"  .cfi_endproc\n"
"\n"
"  .globl say_name\n"
"  .type say_name, @function\n"
"say_name:\n"
"  .cfi_startproc\n"
"  movq %rdi, %r8\n"
"  movl 16(%rdi), %esi\n"
".L.my.loop_start:\n"
"  cmpl $18, %esi\n"
"  js .L.my.loop_end\n"
"  leaq .L.my.str.1(%rip), %rdi\n"
"  movb $0, %al\n"
"  xorl %eax, %eax\n"
"  call printf@plt\n"
"  decl %esi\n"
"  jmp .L.my.loop_start\n"
".L.my.loop_end:\n"
"  movl %esi, 16(%rdx)\n"
"  ret\n"
"  .cfi_endproc\n"
"\n"
"  .type .L.my.str,@object\n"
"  .section .rodata.str1.1,\"aMS\",@progbits,1\n"
".L.my.str:\n"
"  .ascii \"Hello %s, you are %d years old!\\n\\0\"\n"
".L.my.str_end:\n"
"  .size .L.my.str,.L.my.str_end-.L.my.str\n"
"\n"
"  .type .L.my.str.1, @object\n"
".L.my.str.1:\n"
"  .ascii \"%d: Hello %s?\\n\\0\"\n"
".L.my.str.1.end:\n"
"  .size .L.my.str.1,.L.my.str.1.end-.L.my.str.1\n"
"\n"
"  .type .L.my.str.cannot_vote,@object\n"
".L.my.str.cannot_vote:\n"
"  .ascii \"Sorry %s, you cannot vote at %d years old\\n\\0\"\n"
".L.my.str.cannot_vote.end:\n"
"  .size .L.my.str.cannot_vote,.L.my.str.cannot_vote.end-.L.my.str.cannot_vote\n"
"\n"
"  .type .L.my.str.can_vote,@object\n"
".L.my.str.can_vote:\n"
"  .ascii \"Congrats %s, you are okay to vote at %d years old, welcome!\\n\\0\"\n"
".L.my.str.can_vote.end:\n"
"  .size .L.my.str.can_vote,.L.my.str.can_vote.end-.L.my.str.can_vote\n"
"\n"
);

int main(int, char **) {
  struct person me;
  strcpy(&me.name, "John Doe");
  me.age = 16;
  printf("%u\n", sizeof(struct person));
  printf("My name is %s and I am %d years old.\n", me.name, me.age);
  goto start_prog;
adult_age:
  me.age = 23;
start_prog:
  age_state(&me);
  can_vote(&me);
  if (me.age == 16)
    goto adult_age;
  asm(
  "mov $10, %edi\n"
  "call putchar@plt\n"
  );
  say_name(&me);
  printf("My name is %s and I am %d years old.\n", me.name, me.age);
}


