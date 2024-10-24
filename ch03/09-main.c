#include <stdio.h>

short dw_short1(short);
const char *lname(int);

struct person {
  const char *name;
  int age;
};

// This object lives in assembly
extern struct __attribute__((packed)) {
  const char *name;
  int age;
} author;

short dw_short(short x) {
  short y = x / 9, *p = &x, n = 4 * x;
  do {
    x += y;
    *p += 5;
    n -= 2;
  } while (n > 0);
  return x;
}

int main(int argc, char **argv) {
  printf("Hello %s, you are %d years old.\n", author.name, author.age);
  char letters[] = {'A', 'B', 'c', 'd', 'z', 'Z'};
  for (size_t i = 0; i < sizeof(letters); i++)
    printf("%c for %s\n", letters[i], lname(letters[i]));
  printf("lname('z') == lname('Z') = %s\n", lname('Z') == lname('z')?"true":"false");
  short sh[] = { 5, 7, 13 };
  for ( size_t idx = 0; idx < (sizeof(sh) >> 1); idx++ ) {
    printf("dw_short(%d) = %d\n", sh[idx], dw_short(sh[idx]));
    printf("dw_short1(%d) = %d\n", sh[idx], dw_short1(sh[idx]));
  }
}

