#include <stdio.h>

float maxf(float, float);
float minf(float, float);
float sqrtf_(float);
float fand(float, float);
float fxor(float, float);

asm(
  "  .globl maxf\n"
  "  .type maxf, @function\n"
  "maxf:\n"
  "  .cfi_startproc\n"
  "  # maxss %xmm1, %xmm0\n"
  "  ucomiss %xmm1, %xmm0\n"
  "  ja .maxf.end\n"
  "  movss %xmm1, %xmm0\n"
  ".maxf.end:\n"
  "  ret\n"
  "  .cfi_endproc\n"

  "  .globl minf\n"
  "  .type minf, @function\n"
  "minf:\n"
  "  .cfi_startproc\n"
  "  minss %xmm1, %xmm0\n"
  "  ret\n"
  "  .cfi_endproc\n"

  "  .globl sqrtf_\n"
  "  .type sqrtf_, @function\n"
  "sqrtf_:\n"
  "  .cfi_startproc\n"
  "  sqrtss %xmm0, %xmm0\n"
  "  ret\n"
  "  .cfi_endproc\n"

  "  .globl fand\n"
  "  .type fand, @function\n"
  "fand:\n"
  "  .cfi_startproc\n"
  "  andps %xmm1, %xmm0\n"
  "  ret\n"
  "  .cfi_endproc\n"

  "  .globl fxor\n"
  "  .type fxor, @function\n"
  "fxor:\n"
  "  .cfi_startproc\n"
  "  xorps %xmm1, %xmm0\n"
  "  ret\n"
  "  .cfi_endproc\n"
);

int main(int argc, char **argv) {
  float const a = 12.34, b = 56.78;
  printf("maxf(%.2f, %.2f) = %.2f\n", a, b, maxf(a, b));
  printf("maxf(%.2f, %.2f) = %.2f\n", b, a, maxf(b, a));
  printf("minf(%.2f, %.2f) = %.2f\n", a, b, minf(a, b));
  printf("minf(%.2f, %.2f) = %.2f\n", b, a, minf(b, a));
  printf("sqrtf_(%.2f) = %.4f\n", a, sqrtf_(a));
  printf("sqrtf_(%.2f) = %.4f\n", b, sqrtf_(b));
  printf("%f & %f = %f\n", a, b, fand(a, b));
  printf("%f ^ %f = %f\n", a, b, fand(a, b));
}

