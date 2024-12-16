#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <wchar.h>

typedef int data_t;

#ifdef DEBUG
#define SEED 50
#define N 5
#define RAND_MASK 0xf
#define COUNT 1
#define LOOPS 1
#else
#define SEED clock()
#endif

#define CHK_IF 1
#define CHK_CMOV 2
#define CHK_CMOV_LONG 3

#ifndef CHK
#define CHK CHK_IF
#endif

#ifndef N
#define N 1000
#endif

#ifndef LOOPS
#define LOOPS 10000
#endif

#ifndef COUNT
#define COUNT 3
#endif

#ifndef RAND_MASK
#define RAND_MASK 0xffffff
#endif

struct bundle {
  data_t src1[N], src2[N], dest[N * 2];
};

bool is_sorted(data_t dest[]) {
  for (size_t i = 1; i < 2 * N; i++) {
    if (dest[i - 1] > dest[i])
      return false;
  }
  return true;
}

#ifdef NDEBUG
#define is_sorted(bundle) true
#endif

int compare_data_t(void const *a, void const *b) {
  return *(data_t *)a > *(data_t *)b;
}

void bundle_init(struct bundle *data) {
  for (size_t i = 0; i < N; i++) {
    data->src1[i] = rand() & RAND_MASK;
    data->src2[i] = rand() & RAND_MASK;
  }
  qsort(data->src1, N, sizeof(data_t), &compare_data_t);
  qsort(data->src2, N, sizeof(data_t), &compare_data_t);
}

void bundle_show(struct bundle *data) {
  size_t i = 0;
  printf("SRC1 = [");
  for (i = 0; i < N; i++)
    printf("%d, ", data->src1[i]);
  printf("\b\b]\nSRC2 = [");
  for (i = 0; i < N; i++)
    printf("%d, ", data->src2[i]);
  printf("\b\b]\nDEST = [");
  for (i = 0; i < 2 * N; i++)
    printf("%d, ", data->dest[i]);
  printf("\b\b]\n");
}

#ifdef NDEBUG
#define bundle_show(arg)
#endif

void merge_sort(data_t src1[], data_t src2[], data_t dest[]) {
  size_t i1 = 0, i2 = 0, id = 0;
  while (i1 < N && i2 < N) {
#if CHK == CHK_IF
    if (src1[i1] < src2[i2])
      dest[id++] = src1[i1++];
    else
      dest[id++] = src2[i2++];
#elif CHK == CHK_CMOV
    dest[id++] = src1[i1] < src2[i2] ? src1[i1++] : src2[i2++];
#elif CHK == CHK_CMOV_LONG
    int cond = src1[i1] < src2[i2];
    dest[id++] = cond ? src1[i1] : src2[i2];
    i1 += cond;
    i2 += (1 - cond);
#else
#error "CHK was not set."
#endif
  }
  while (i1 < N)
    dest[id++] = src1[i1++];
  while (i2 < N)
    dest[id++] = src2[i2++];
  assert(id == 2 * N);
  assert(is_sorted(dest));
}

void draw_progress_bar(int current) {
  assert(current >= 0 && current <= 100);
  printf("\r\e[37;1m%3d%% \u2768\e[32;1m", current);
  int left = 100 - current;
  /*printf("•");*/
  for (; current; --current)
    printf("\u2501");
  printf("\e[34;1m\u2022\e[31;1m");
  for (; left; --left)
    printf("\u2501");
  printf("\e[37;1m\u2769\e[0m ");
  fflush(stdout);
}

void test_progress_bar() {
  for (int i = 0; i <= 100; i++) {
    draw_progress_bar(i);
    printf("Testing progress bar");
    usleep(10000);
  }
  putchar('\n');
}

#ifdef NDEBUG
#define test_progress_bar()
#endif

double measure_cpe(struct bundle *data) {
  clock_t total = 0;
  for (size_t counter = 1; counter <= LOOPS; counter++) {
    bundle_init(data);
    clock_t lapse = clock();
    merge_sort(data->src1, data->src2, data->dest);
    total += clock() - lapse;
    bundle_show(data);
    draw_progress_bar((counter * 100) / LOOPS);
    printf("Measuring CPE");
  }
  putchar('\n');
  return (double)total / (2 * N * LOOPS);
}

double average_cpe(struct bundle *data) {
  double cpe = 0;
  for (size_t i = 0; i < COUNT; i++)
    cpe += measure_cpe(data);
  return cpe / COUNT;
}

int main(int argc, char *argv[]) {
  test_progress_bar();
  srand(SEED);
  struct bundle data;
  double cpe = average_cpe(&data);
  printf("SORTED=%d LOOPS=%d N=%d CPE=%lf\n", is_sorted(data.dest), LOOPS, N,
         cpe);
}
