#include<stdlib.h>
#include<stdint.h>

static inline uint32_t log2(const uint32_t x) {
  uint32_t y;
  asm ( "\tbsr %1, %0\n"
      : "=r"(y)
      : "r" (x)
  );
  return y;
}

int main(void) {
  long i;
  uint32_t r;
  for (i = 0; i < 10000000000; i++) {
    r ^= (2 << log2(42)) + 42;
  }
  return r;
}
