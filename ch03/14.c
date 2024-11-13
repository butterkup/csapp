#include "14.h"
#include <stdio.h>

void print(struct value *v) {
  printf("Value{ a=%d, b=%f }\n", v->a, v->b);
}
