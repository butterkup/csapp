#include "utils.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>

#ifndef DATA_T
#define DATA_T int
#endif

typedef DATA_T data_t;

#ifndef FDATA_T
#define FDATA_T "%d"
#endif

#define NULLMATRIX                                                             \
  (Matrix) { .rows = 0, .cols = 0, .data = NULL }

typedef struct matrix {
  unsigned rows, cols;
  data_t *data;
} Matrix;

Matrix matrix_create(const unsigned rows, const unsigned cols) {
  if (rows == 0 || cols == 0) {
    return NULLMATRIX;
  }
  data_t *data = (data_t *)calloc(rows * cols, sizeof(data_t));
  debug("Creating(%ux%u %lu %lu): %p\n", rows, cols, sizeof(data_t),
        rows * cols * sizeof(data_t), data);
  if (data == NULL) {
    debug("> Creation failed: %d - %s.\n", errno, strerror(errno));
    exit(errno);
  }
  debug("> Created %p\n", data);
  return (Matrix){.rows = rows, .cols = cols, .data = data};
}

void matrix_destroy(Matrix *const matrix) {
  debug("Destroying(%ux%u): %p\n", matrix->rows, matrix->cols, matrix->data);
  if (matrix->data != NULL)
    free(matrix->data);
  debug("> Destroyed %p\n", matrix->data);
  *matrix = NULLMATRIX;
}

void matrix_fprint(FILE *stream, const Matrix *const matrix) {
  fprintf(stream, "(Matrix[%ux%u]) [\n", matrix->rows, matrix->cols);
  for (unsigned row = 0; row < matrix->rows; row++) {
    fprintf(stream, " [ ");
    for (unsigned col = 0; col < matrix->cols; col++) {
      fprintf(stream, FDATA_T ", ", matrix->data[row * matrix->cols + col]);
    }
    fprintf(stream, "\b\b ],\n");
  }
  fprintf(stream, "]\n");
}

void matrix_print(const Matrix *const matrix) { matrix_fprint(stdout, matrix); }

void matrix_mul_impl_1(const Matrix *const mat1, const Matrix *const mat2,
                       Matrix *const mat3) {
  for (unsigned row = 0; row < mat3->rows; row++) {
    for (unsigned col = 0; col < mat3->cols; col++) {
      data_t sum = 0;
      // mat1->cols == mat2->rows
      for (unsigned tmp = 0; tmp < mat1->cols; tmp++) {
        sum += mat1->data[row * mat1->cols + tmp] *
               mat2->data[tmp * mat2->cols + col];
      }
      mat3->data[row * mat3->cols + col] = sum;
    }
  }
}

void matrix_mul_impl_2(const Matrix *const mat1, const Matrix *const mat2,
                       Matrix *const mat3) {
  for (unsigned col = 0; col < mat3->cols; col++) {
    for (unsigned row = 0; row < mat3->rows; row++) {
      data_t sum = 0;
      // mat1->cols == mat2->rows
      for (unsigned tmp = 0; tmp < mat1->cols; tmp++) {
        sum += mat1->data[row * mat1->cols + tmp] *
               mat2->data[tmp * mat2->cols + col];
      }
      mat3->data[row * mat3->cols + col] = sum;
    }
  }
}

#ifndef MATMULIMPL
#define MATMULIMPL 1
#endif
#define XCONCAT(x, y) x##y
#define CONCAT(x, y) XCONCAT(x, y)

int matrix_mul(const Matrix *const mat1, const Matrix *const mat2,
               Matrix *const mat3) {
  if (mat1->cols != mat2->rows) {
    return 1;
  }
  if (mat3->rows != mat1->rows && mat3->cols != mat2->cols) {
    return 2;
  }
  CONCAT(matrix_mul_impl_, MATMULIMPL)(mat1, mat2, mat3);
  return 0;
}

void matrix_rand(Matrix *const matrix, const size_t mask) {
  for (unsigned col = 0; col < matrix->cols; col++) {
    for (unsigned row = 0; row < matrix->rows; row++) {
      matrix->data[row * matrix->cols + col] = rand() & mask;
    }
  }
}

#ifndef DIM_A
#define DIM_A 60
#endif

#ifndef DIM_B
#define DIM_B 80
#endif

#ifndef DIM_C
#define DIM_C 100
#endif

const unsigned a = DIM_A, b = DIM_B, c = DIM_C;
const unsigned arena_size = a * b + b * c + a * c;

void iota(data_t *array, size_t n, data_t start) {
  for (size_t idx = 0; idx < n; idx++, start++) {
    array[idx] = start;
  }
}

struct matmul_args {
  const Matrix *const mat1, *const mat2;
  Matrix *const mat3;
};

void matmul_func(void *arg) {
  struct matmul_args *args = arg;
  matrix_mul(args->mat1, args->mat2, args->mat3);
}

struct matmul_init_args {
  size_t mask;
  Matrix *const mat1, *const mat2;
};

void matmul_init_func(void *arg) {
  struct matmul_init_args *args = arg;
  matrix_rand(args->mat1, args->mask);
  matrix_rand(args->mat2, args->mask);
}

#ifndef AVGCNT
#define AVGCNT 100
#endif

#ifndef RANDSEED
#define RANDSEED time(NULL)
#endif

int main() {
  srand(RANDSEED);
#ifndef ALLOCATE_ARENA
  // Allocate arena from the stack
  data_t arena[arena_size];
#else
  // Allocate arena from the heap
  data_t *arena = calloc(arena_size, sizeof(data_t));
#endif
  // Create matrices that are views into the arena's memory
  Matrix mat1 = (Matrix){.rows = a, .cols = b, .data = &arena[0]};
  Matrix mat2 = (Matrix){.rows = b, .cols = c, .data = &arena[a * b]};
  Matrix mat3 = (Matrix){.rows = a, .cols = c, .data = &arena[b * (a + c)]};

  struct matmul_init_args init_args =
      (struct matmul_init_args){.mask = -1, .mat1 = &mat1, .mat2 = &mat2};
  Task matmul_init_task =
      (Task){.function = matmul_init_func, .argument = &init_args};
  struct matmul_args args =
      (struct matmul_args){.mat1 = &mat1, .mat2 = &mat2, .mat3 = &mat3};
  Task matmul_task = (Task){.function = matmul_func, .argument = &args};

  double avg_time = task_average_timer(matmul_init_task, matmul_task, AVGCNT);
#ifdef MATRICES_FPRINT_STDERR
  matrix_fprint(stderr, &mat1);
  matrix_fprint(stderr, &mat2);
  matrix_fprint(stderr, &mat3);
#endif
  printf("Average time: %lf\n", avg_time);

#ifdef ALLOCATE_ARENA
  free(arena);
#endif
}
