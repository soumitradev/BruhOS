#pragma once

#include <stdint.h>

#define low_16(address) (uint16_t)((address)&0xFFFF)
#define high_16(address) (uint16_t)((address >> 16) & 0xFFFF)
#define low_32(address) (uint16_t)((address)&0xFFFFFFFF)
#define high_32(address) (uint16_t)((address >> 32) & 0xFFFFFFFF)

class BitMap {
 public:
  uint8_t *bitmap_base;
  uint64_t size;
  BitMap(uint8_t *base, uint64_t size);
  void set_bit(uint64_t idx);
  void clr_bit(uint64_t idx);
  bool get_bit(uint64_t idx);
  void print_bmp(uint64_t start, uint64_t length);
};