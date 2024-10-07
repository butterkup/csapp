#include <stdio.h>
#include <stdbool.h>

int uadd_ok(unsigned x, unsigned y) {
  return x + y < x;
}

int tadd_ok(int x, int y) {
  if( x < 0 && y < 0)
    return x + y >= 0;
  else if(x > 0 && y > 0)
    return x + y < 0;
  else return 0;
}

const char *boolstr(bool value) {
  return value? "true": "false";
}

void check_uoverflow(unsigned v[][2], size_t len) {
  printf("len = %u\n", len);
  for(size_t i = 0; i < len; i++)
    printf(
        "%u + %u = %u : %s\n",
        v[i][0], v[i][1], v[i][0] + v[i][1], 
        boolstr(uadd_ok(v[i][0], v[i][1]))
    );
}

void check_toverflow(int v[][2], size_t len) {
  printf("len = %u\n", len);
  for(size_t i = 0; i < len; i++)
    printf(
        "%d + %d = %d : %s\n",
        v[i][0], v[i][1], v[i][0] + v[i][1],
        boolstr(tadd_ok(v[i][0], v[i][1]))
    );
}

int main() {
  unsigned uvalues[][2] = {
    { 1024, 2048 },
    { 0xFFFFFFFF, 0x1 },
    { 0xFFFF0000, 0x0001FFFF },
    { 0xF0F0F0F0, 0x0F0F0F0F },
    { 0xFFF00000, 0x00000FFF },
    { 0xFFFFFFFF, 1 },
    { 1, 0xFFFFFFFF },
    { 0xFFFFFFFF, 0 },
    { 0, 0xFFFFFFFF }
  };
  // check_uoverflow(uvalues, sizeof(uvalues) >> 3);
  int tvalues[][2] = {
    { 5052, 4567 },
    { 0x8000FFFF, 0xFFFF0000 },
    { 0x8000FF00, 0x000000FF },
    { 0xFFFF0000, 0x0000FFFF },
    { 0xFFFF0F0F, 0x8000F0F0 },
    { 0x80000000, 0x7FFFFFFF },
    { 0x7FFF8000, 0x0000FFFF }
  };
  check_toverflow(tvalues, sizeof(tvalues) >> 3);
}

