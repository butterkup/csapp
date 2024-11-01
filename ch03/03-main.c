#include <stdio.h>

struct person {
  const char *name;
  long age;
};

struct person person_init(const char *name, int age) {
  return (struct person){
    .name = name,
    .age = age
  };
}

struct person person_init2() {
  return person_init(NULL, 0);
}

void person_print(struct person *p) {
  printf("person(name='%s', age=%ld)",
      p->name, p->age);
}

int main(int argc, char **argv) {
  struct person me = person_init("Simon Nganga", 22);
  person_print(&me);
  putchar('\n');
}

