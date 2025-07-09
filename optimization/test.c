#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <time.h>
#include <inttypes.h>

#include "../util.h"

extern void multiply_matrices(uint64_t *a, uint64_t *b, uint64_t *c, size_t n);
extern void multiply_matrices_optimized(uint64_t *a, uint64_t *b, uint64_t *c, size_t n);
extern void multiply_matrices_jazz(uint64_t *a, uint64_t *b, uint64_t *c, size_t n);
extern void multiply_matrices_optimized_jazz(uint64_t *a, uint64_t *b, uint64_t *c, size_t n);

void run_test(const char *label,
              void (*func)(uint64_t*, uint64_t*, uint64_t*, size_t),
              uint64_t *a, uint64_t *b, uint64_t *c, size_t n)
{
    flush_cache();
    uint64_t start = get_cycles();
    func(a, b, c, n);
    uint64_t end = get_cycles();
    printf("%s:\n", label);
    printf("Cycles: %" PRIu64 "\n", end - start);
}

int main() {
    size_t n = 100;

    size_t matrix_size = n * n * sizeof(uint64_t);
    uint64_t *a = malloc(matrix_size);
    uint64_t *b = malloc(matrix_size);
    uint64_t *c_O0 = malloc(matrix_size);
    uint64_t *c_O3 = malloc(matrix_size);
    uint64_t *c_jazz = malloc(matrix_size);
    uint64_t *c_jazz_O3 = malloc(matrix_size);

    if (!a || !b || !c_O0 || !c_O3 || !c_jazz || !c_jazz_O3) {
        fprintf(stderr, "malloc failed\n");
        return 1;
    }

    for (size_t i = 0; i < n; i++)
        for (size_t j = 0; j < n; j++) {
            a[i * n + j] = i + j;
            b[i * n + j] = (i == j);
        }

    run_test("C -O0", multiply_matrices, a, b, c_O0, n);
    run_test("C -O3", multiply_matrices_optimized, a, b, c_O3, n);
    run_test("Jasmin -O0", multiply_matrices_jazz, a, b, c_jazz, n);
    run_test("Jasmin -O3", multiply_matrices_optimized_jazz, a, b, c_jazz_O3, n);

    bool ok = true;
    for (size_t i = 0; i < n * n; i++) {
        if (c_O0[i] != c_O3[i] || c_O0[i] != c_jazz[i] || c_O0[i] != c_jazz_O3[i]) {
            ok = false;
            break;
        }
    }

    if (!ok) {
        printf("Error: outputs do not match!\n");
    } else {
        printf("All implementations match.\n");
    }

    free(a); free(b);
    free(c_O0); free(c_O3);
    free(c_jazz); free(c_jazz_O3);
    return 0;
}
