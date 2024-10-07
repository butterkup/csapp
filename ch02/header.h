#pragma once

#include <stdio.h>
#include <endian.h>

#define FORLOOP(var, len) (int var = 0; var < len; var++)

#ifdef BIGEND // Please use BIG_ENDIANNESS
# if BYTE_ORDER == LITTLE_ENDIAN
#  undef FORLOOP
#  define FORLOOP(var, len) (int var = len - 1; var >= 0; var--)
# elif BYTE_ORDER == BIG_ENDIAN
# else
#  error "Unknown ENDIANNESS"
# endif
#endif

typedef unsigned char* byte_pointer;

void show_bits(byte_pointer start, size_t len) {
  for FORLOOP(j, len) {
    putchar(' ');
    for (int i = 7; i >= 0; i--)
      putchar((start[j] & (1 << i)) ? '1' : '0');
    // printf("(%.2X)", start[j]);
  }
#ifndef NONL
  putchar('\n');
#endif
}

void show_bytes(byte_pointer start, size_t len) {
  for FORLOOP(i, len)
    printf(" %.2X", start[i]);
#ifndef NONL
  putchar('\n');
#endif
}

#define show_t(type)                             \
  void show_##type(type x) {              \
    show_bytes((byte_pointer)&x, sizeof(type));  \
  }

typedef unsigned short ushort;
typedef unsigned int uint;
typedef unsigned long ulong;

show_t(float)
show_t(double)
show_t(int)
show_t(long)
show_t(short)
show_t(uint)
show_t(ushort)
show_t(ulong)

#undef show_t

