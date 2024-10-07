#include <stdio.h>
#include "header.h"

#define pexpr(expr) printf(#expr " = 0x%.8X\n", expr)

void bitwise(void) {
  unsigned int G = 0x87654321;
  puts("Bitwise.");
  pexpr(G);
  pexpr(G & 0xFF);
  pexpr((~G & 0xFFFFFF00) | (G & 0xFF));
  pexpr(G ^ ~0xFF);
  pexpr(G | 0xFF);
}

void shifts(void) {
  signed int a, b;
  unsigned int c, d;
  puts("Signed.");
  a = 0x87654321;
  b = 0x12345678;
  pexpr(a);
  pexpr(b);
  pexpr(a << 12);
  pexpr(a >> 12);
  pexpr(b >> 12);
  pexpr(b << 12);
//pexpr(a >> 40);
//pexpr(b << 40);
  puts("Unsigned.");
  c = 0x87654321;
  d = 0x12345678;
  pexpr(c);
  pexpr(d);
  pexpr(c << 12);
  pexpr(c >> 12);
  pexpr(d << 12);
  pexpr(d >> 12);
//pexpr(c >> 40);
//pexpr(d << 40);
}

void bitseq(void) {
  signed int a = 0xFFFFFFFFu;
  printf("0xFFFFFFFF = %d\n", a);
  printf("0xFFFFFFFF = %u\n", a);
}

int page(short v) {
  printf("Age = %d\n", v);
  return v + 90;
}

int expand() {
  short sx = -12345;
  unsigned short usx = sx;
  int x = sx;
  unsigned ux = usx;
  
  printf("sx = %d: ", sx);
  show_short(sx);
  printf("usx = %u: ", usx);
  show_ushort(usx);
  printf("x = %d: ", x);
  show_int(x);
  printf("ux = %u: ", ux);
  show_uint(ux);
  ux = sx;
  printf("ux = %u: ", ux);
  show_uint(ux);
}

#define KSIZE 1024

int _cpfkbsd(int maxlen) {
  int len = KSIZE < maxlen? KSIZE :maxlen;
  // memcpy from kernel- to user-buffer code goes here...
  return len;
}

#undef KSIZE

void cpfkbsd(int maxlen) {
  printf("----------------------------------\n");
  printf("maxlen = %d = %u\n", maxlen, maxlen);
  int len = _cpfkbsd(maxlen);
  printf("len    = %d = %u\n", len, len);
  printf("----------------------------------\n");
}

void cpfkbsd_(int *maxlens, size_t len) {
  for(size_t i = 0; i < len; i++)
    cpfkbsd(maxlens[i]);
}

#undef pexpr

int main(void) {
  int maxlens[] = {
    0, 512, 2048, -512
  };
  cpfkbsd_(maxlens, 4u);
  // expand();
  // page(0x80000015);
  // page(0x15);
  // bitseq();
  // shifts();
  // bitwise();
}

