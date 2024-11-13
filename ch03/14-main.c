#include <stdio.h>
#include "14.h"

float u2f(unsigned v) { return (float)v; }
float i2f(int v) { return (float)v; }
float uasf(unsigned v) { return *(float *)&v; }
unsigned fasu(float v) { return *(unsigned *)&v; }

int main() {
  print(&(struct value){ .a=34, .b=45.75f });
  printf("-2 = %u = %f\n", -2, u2f(-2));
  printf("-2 = %d = %f\n", -2, i2f(-2));
  printf("-2 = %f\n", uasf(0x4f800000));
  printf("100.0 = 0x%x\n", fasu(100.0));
  return 0;
}
