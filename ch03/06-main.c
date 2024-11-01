#include <stdio.h>

struct person  {
  const char *name;
  int age;
  struct {
    long a;
    int b;
    float c;
    double d;
  } others;
};

void person_init(struct person* _) {
  asm(
    "movq    $0x64,              8(%rdi)    # <-- age\n"
    "movabsq $0xFFFFFFFF,        %rax\n"
    "movq    %rax,                16(%rdi)  # <-- others.a\n"
    "movl    $0xFFFF,             24(%rdi)  # <-- others.b\n"
    "movl    $0x42C88000,         28(%rdi)  # <-- others.c\n"
    "movabsq $0x4059100000000000, %rax\n"
    "movq    %rax,                32(%rdi)  # <-- others.d\n"
  );
}

void print_person(struct person *p) {
  printf(
    "Hello: { .name='%s', .age=%d, .others="
    "{ .a=%ld, .d=%d, .c=%f, .d=%lf } }\n",
    p->name, p->age, p->others.a, p->others.b,
    p->others.c, p->others.d
  );
}

int main(int argc, char **argv) {
  struct person me = {
    .name="John Doe",
    .age=22,
    .others={
      .a=0x1122334455667788,
      .b=0x44332211,
      .c=1234.5678f,
      .d=87654321.12345678
    }
  }, me2;
  me2.name = "Jane Doe";
  printf("sizeof(struct person) = %zu\n", sizeof(struct person));
  person_init(&me2);
  print_person(&me2);
  print_person(&me);
}
