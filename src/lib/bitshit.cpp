#include <stdint.h>

#include <kernel/drivers/screen.hpp>
#include <lib/bitshit.hpp>
#include <lib/strutils.hpp>

BitMap::BitMap(uint8_t *base, uint64_t size) {
  bitmap_base = base;
  size = size;
}

void BitMap::set_bit(uint64_t idx) {
  uint8_t bit = idx % 8;
  uint64_t byte = idx / 8;
  bitmap_base[byte] |= (1 << bit);
}

void BitMap::clr_bit(uint64_t idx) {
  uint8_t bit = idx % 8;
  uint64_t byte = idx / 8;
  bitmap_base[byte] &= ~(1 << bit);
}

uint8_t BitMap::get_bit(uint64_t idx) {
  uint8_t bit = idx % 8;
  uint64_t byte = idx / 8;
  return bitmap_base[byte] & (1 << bit);
}

void BitMap::print_bmp() {
  for (uint64_t i = 0; i < size; i++) {
    print(itob(get_bit(i), 2));
  }
}