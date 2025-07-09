#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <inttypes.h>

#define GET_TIME(start, end) (((end) - (start)) / CLOCKS_PER_SEC)
#define GET_CYCLES(start, end) ((end) - (start))

static inline uint64_t get_cycles() {
  uint32_t low, high;
  __asm__ volatile("rdtsc" : "=a"(low), "=d"(high));
  return ((uint64_t)high << 32) | low;
}

#define CACHE_FLUSH_SIZE (12 * 1024 * 1024)

void flush_cache() {
  static char *buffer = NULL;
  if (!buffer) {
    buffer = (char *)malloc(CACHE_FLUSH_SIZE);
    if (!buffer) {
      perror("malloc");
      return;
    }
    for (size_t i = 0; i < CACHE_FLUSH_SIZE; i++) {
      buffer[i] = (char)i;
    }
  }

  volatile char sum = 0;
  for (size_t i = 0; i < CACHE_FLUSH_SIZE; i++) {
    sum += buffer[i];
  }
  if (sum == 0xFF) printf("Impossible\n");
}