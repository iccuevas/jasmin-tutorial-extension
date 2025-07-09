#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include "../util.h"

#define NUM_BLOCKS 160
#define NRUNS 1000

#define U64_TERNARY(boolval, u64true, u64false) \
  (((0 - ((boolval) != false)) & u64true) | (((UINT64_MAX + ((boolval) != false)) & u64false)))

#define BLOCK_DATA_SIZE_QWORDS 168

typedef uint64_t u64;

typedef struct block block;
struct block
{
  u64 id;
  u64 position;
  u64 data[BLOCK_DATA_SIZE_QWORDS];
};

extern void odd_even_msort(block* blocks, u64* block_level_assignments, size_t lb, size_t ub);
extern void odd_even_msort_jazz(block* blocks, u64* block_level_assignments, size_t lb, size_t ub);

void initialize_blocks(block* blocks, u64 *block_level_assignment, size_t num_blocks) {
  for (size_t i = 0; i < num_blocks; ++i) {
    blocks[i].id = rand();
    blocks[i].position = rand();
    for (size_t j = 0; j < BLOCK_DATA_SIZE_QWORDS; ++j) {
        blocks[i].data[j] = rand() % 1000;
    }
  }
  for (size_t i = 0; i < NUM_BLOCKS; ++i) {
    block_level_assignment[i] = (((u64)rand() << 32) | rand())%1000;
  }
}

int main() {
  struct timespec start, end;
  double c_time = 0, j_time;
  srand((unsigned)time(NULL));

  block *blocks = calloc(NUM_BLOCKS, sizeof(block));
  block *blocks_jazz = calloc(NUM_BLOCKS, sizeof(block));
  u64 *block_level_assignment = calloc(NUM_BLOCKS, sizeof(u64));
  u64 *block_level_assignment_jazz = calloc(NUM_BLOCKS, sizeof(u64));

  for (size_t i=0;i<NRUNS;i++) {
    initialize_blocks(blocks, block_level_assignment, NUM_BLOCKS);
    memcpy(blocks_jazz, blocks, sizeof(block) * NUM_BLOCKS);
    memcpy(block_level_assignment_jazz, block_level_assignment, sizeof(u64) * NUM_BLOCKS);

    clock_gettime(CLOCK_MONOTONIC, &start);
    odd_even_msort(blocks, block_level_assignment, 0, NUM_BLOCKS);
    clock_gettime(CLOCK_MONOTONIC, &end);
    c_time += (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;

    flush_cache();

    clock_gettime(CLOCK_MONOTONIC, &start);
    odd_even_msort_jazz(blocks_jazz, block_level_assignment_jazz, 0, NUM_BLOCKS);
    clock_gettime(CLOCK_MONOTONIC, &end);
    j_time += (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
  }

  printf("C time:      %.6f seconds\n", c_time);
  printf("Jasmin time: %.6f seconds\n", j_time);

  return 0;
}
