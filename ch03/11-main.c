#include <stdio.h>

#if 0
typedef double mat_t;
#define _mat_t_fmt "%4.2lf"
#else
typedef int mat_t;
#define _mat_t_fmt "%3d"
#endif

void matmul(size_t const r1, size_t const c1r2, size_t const c2,
            mat_t const (*const A)[r1][c1r2], mat_t const (*const B)[c1r2][c2],
            mat_t (*const C)[r1][c2]) {
  for (size_t i = 0; i < r1; i++) {
    for (size_t j = 0; j < c2; j++) {
      mat_t dot = 0;
      for (size_t k = 0; k < c1r2; k++)
        dot += (*A)[i][k] * (*B)[k][j];
      (*C)[i][j] = dot;
    }
  }
}

void matbop(size_t const r, size_t const c, mat_t (*const A)[r][c],
            mat_t const (*const B)[r][c],
            mat_t (*const binary_op)(mat_t, mat_t)) {
  for (size_t i = 0; i < r; i++)
    for (size_t j = 0; j < c; j++)
      (*A)[i][j] = binary_op((*A)[i][j], (*B)[i][j]);
}

void matuop(size_t const r, size_t const c, mat_t (*const A)[r][c],
            mat_t (*const unary_op)(mat_t)) {
  for (size_t i = 0; i < r; i++)
    for (size_t j = 0; j < c; j++)
      (*A)[i][j] = unary_op((*A)[i][j]);
}

void matprint(size_t const r, size_t const c, mat_t const (*const M)[r][c]) {
  puts("[");
  for (size_t i = 0; i < r; i++) {
    printf("    ");
    for (size_t j = 0; j < c; j++)
      printf(_mat_t_fmt ", ", (*M)[i][j]);
    putchar('\n');
  }
  putchar(']');
}

mat_t _mat_bop_add(mat_t const a, mat_t const b) { return a + b; }
mat_t _mat_bop_sub(mat_t const a, mat_t const b) { return a - b; }
mat_t _mat_bop_mul(mat_t const a, mat_t const b) { return a * b; }
mat_t _mat_bop_div(mat_t const a, mat_t const b) { return a / b; }

static double scalar;
mat_t scale(mat_t x) { return x * scalar; }
mat_t sqr(mat_t x) { return x * x; }
mat_t recpr(mat_t x) { return 1 / x; }

int main() {
  mat_t A[3][5] = {{1, 2, 3, 4, 5}, {6, 7, 8, 9, 10}, {11, 12, 13, 14, 15}};
  mat_t B[5][4] = {{20, 19, 18, 17},
                   {16, 15, 14, 13},
                   {12, 11, 10, 9},
                   {8, 7, 6, 5},
                   {4, 3, 2, 1}};
  mat_t C[3][4];
  matmul(3, 5, 4, &A, &B, &C);
  printf("A = ");
  matprint(3, 5, &A);
  printf("\nB = ");
  matprint(5, 4, &B);
  printf("\nC = ");
  matprint(3, 4, &C);
  putchar('\n');
}
