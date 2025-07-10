#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

uint64_t register_pressure(uint64_t arg1, uint64_t arg2, uint64_t arg3,
                           uint64_t arg4, uint64_t arg5, uint64_t arg6);

extern
uint64_t register_pressure_jazz(uint64_t arg1, uint64_t arg2, uint64_t arg3,
                                uint64_t arg4, uint64_t arg5, uint64_t arg6);

void main(void) {
  uint64_t a, b, c, d, e, f, r0, r1;

  r0 = register_pressure(12, 34, 56, 78, 90, 123);
  r1 = register_pressure_jazz(12, 34, 56, 78, 90, 123);
  if (r0 != r1) fprintf(stderr, "ERROR: %zu != %zu\n", r0, r1);

  r0 = register_pressure(987, 654, 321, 123, 456, 789);
  r1 = register_pressure_jazz(987, 654, 321, 123, 456, 789);
  if (r0 != r1) fprintf(stderr, "ERROR: %zu != %zu\n", r0, r1);

  r0 = register_pressure(2023, 4046, 8088, 1001, 7777, 8888);
  r1 = register_pressure_jazz(2023, 4046, 8088, 1001, 7777, 8888);
  if (r0 != r1) fprintf(stderr, "ERROR: %zu != %zu\n", r0, r1);
}