#pragma once

#include <stdint.h>

// Write our own epic (unoptimised 😳) memcpy
template <typename T>
void memory_copy(T *source, T *dest, uint64_t nelems) {
  for (uint64_t i = 0; i < nelems; i++) {
    *(dest + i) = *(source + i);
  }
}

// Write our own epic (unoptimised 😳) memset
template <typename T>
void memory_set(T *dest, T val, uint64_t len) {
  T *temp = (T *)dest;
  for (; len != 0; len--) *temp++ = val;
}
