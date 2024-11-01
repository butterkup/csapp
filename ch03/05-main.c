#include <stdio.h>

typedef unsigned __int128 uint128_t;

union value {
  struct { long a, b; } args;
  long double result;
};

void mult(union value* v) {
  v->result = v->args.a * (uint128_t) v->args.b;
}

void mult2(union value *_) {
  asm(
    "movq   (%rdi), %rax\n"
    "imulq  8(%rdi)\n"
    "movq   %rdx, (%rdi)\n"
    "movq   %rax, 8(%rdi)\n"
  );
}

void remdiv(union value *v) {
  long a = v->args.a, b = v->args.b;
  v->args.a = a / b;
  v->args.b = a % b;
}

void remdiv2(union value *_) {
  asm(
    "movq   (%rdi), %rax\n"
    "cqto\n"
    "idivq  8(%rdi)\n"
    "movq   %rax, (%rdi)\n"
    "movq   %rdx, 8(%rdi)\n"
  );
}

int main(int argc, char **argv) {
  union value _v = {
    .args = {
      .a = 0x1001001001001001,
      .b = 0x0000000100000000
    }
  }, v = _v;
  printf("%ld * %ld = ", v.args.a, v.args.b); mult(&v);
  printf("[%ld,%ld] -> %Lf\n", v.args.a, v.args.b, v.result);
  v = _v;
  printf("%ld * %ld = ", v.args.a, v.args.b); mult2(&v);
  printf("[%ld,%ld] -> %Lf\n", v.args.a, v.args.b, v.result);
  
  v = _v;
  printf("%ld / %ld = ", v.args.a, v.args.b); remdiv(&v);
  printf("[%ld,%ld] -> %Lf\n", v.args.a, v.args.b, v.result);
  v = _v;
  printf("%ld / %ld = ", v.args.a, v.args.b); remdiv2(&v);
  printf("[%ld,%ld] -> %Lf\n", v.args.a, v.args.b, v.result);
}

