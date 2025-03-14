#include "dllhdr.h"
#include <stdio.h>

int person_age_by(Person *p, int years) {
  if (years < 0) {
    return 1;
  }
  p->age += years;
  return 0;
}

void person_greet(FILE *stream, Person *p) {
  person_age_by(p, 13);
  fprintf(stream,
          "Hello %s? You are %d years old, this greeting"
          " just cost you 13 years, you are young nomore!\n",
          p->name, p->age);
}
