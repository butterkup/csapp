#include "header.h"

int fun1(unsigned word) {
  return (int)((word << 24) >> 24);
}

int fun2(unsigned word) {
  return ((int)word << 24) >> 24;
}

void _shift(unsigned word) {
  show_uint(word);
  printf(" |");
  show_int(fun1(word));
  printf(" |");
  show_int(fun2(word));
  puts(" |");
}

void shift(unsigned *word, int len) {
  puts(" word        | fun1(word)  | fun2(word)  |");
  for (int i = 0; i < len; i++)
    _shift(word[i]);
}

void trun(int w) {
  printf("trun(%d) = %d\n", w, (int)(short)w);
}

int main() {
  unsigned uns[] = {
    0x00000076u,
    0x87654321u,
    0x000000C9u,
    0xEDCBA987u
  };
  // shift(uns, 4);
  trun(53191);
  return 0;
  show_int(0x12345678);
  show_long(0x1234567890ABCDEF);
  show_float(100.25f);
  show_double(100.25);
  show_bytes("abcde", 6);
  show_bytes("12345", 6);
}
