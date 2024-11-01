#include <stdio.h>

struct call_bundle {
  int(*function)(int, int, int);
  int a, b, c, result;
};

int call_function(int(*function)(int, int), int, int);
void exec_bundle(struct call_bundle*);
void helloTn(const char*, int);
void greet_people(const char **, size_t);

int multiply(int, int);

int aPb(int a, int b) {
  printf("%d + %d = %d\n", a, b, a + b);
  return a + b;
}

int aTbPc(int a, int b, int c) {
  printf("%d * %d + %d = %d\n", a, b, c, a * b + c);
  return a * b + c;
}

int main(int argc, char**argv) {
  const char *people[] = {
    "Simon", "Faith", "David",
    "Charles", "Darius", "Lydia"
  };
  int result = call_function(&aPb, 12, 13);
  printf("result = %d\n", result);
  result = call_function(&multiply, 34, 9);
  printf("result = %d\n", result);
  helloTn("John Doe", 5);
  struct call_bundle bundle = {
    .function = &aTbPc,
    .a = 15, .b = 16, .c = 10
  };
  exec_bundle(&bundle);
  printf("bundle.result = %d\n", bundle.result);
  greet_people(people, sizeof(people) >> 3);
}

