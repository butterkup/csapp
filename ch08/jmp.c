#include <setjmp.h>
#include <stdio.h>

jmp_buf env;

int err1 = 1;
int err2 = 1;
int err3 = 1;

void baz() {
  if (err3) {
    err3 = 0;
    longjmp(env, 3);
  }
}

void bar() {
  if (err2) {
    err2 = 0;
    longjmp(env, 2);
  }
  baz();
}

void foo() {
  if (err1) {
    err1 = 0;
    longjmp(env, 1);
  }
  bar();
}

int main() {
  // Error handling section for foo
  switch (setjmp(env)) {
  case 3:
    puts("Error from baz");
    break;
  case 2:
    puts("Error from bar");
    break;
  case 1:
    puts("Error from foo");
    break;
  }
  foo();
  puts("This is printed way after nonlocal jumps to error handlers");
}
