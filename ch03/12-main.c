#include <stdio.h>

int add(int const a, int const b);

void add_show(int const a, int const b, int (*const add_ref)(int const, int const)) {
  printf("%d + %d = %d\n", a, b, add_ref(a, b));
}

int main(int argc, char**argv) {
  int (*const add_ref)(int, int) = &add;
  printf("%d + %d = %d\n", 56, 44, add_ref(56, 44));
  add_show(78, 72, add);
}

asm(
  ".globl add\n"
  ".type add, @function\n"
"add:\n"
 ".cfi_startproc\n"
 "movl %edi, %eax\n"
 "addl %esi, %eax\n"
 "ret\n"
 ".cfi_endproc\n"
);

