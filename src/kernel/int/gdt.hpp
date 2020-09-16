#pragma once

#include <stdint.h>

extern "C" void lgdt(uint64_t gdtAddr);

struct gdt_ptr {
  uint16_t limit;
  uint64_t base;
} __attribute__((packed));

struct gdt_desc {
  uint16_t limit_low16;
  uint16_t base_low16;
  uint8_t base_mid8;
  uint16_t flags;
  uint8_t base_high8;
} __attribute__((packed));

struct gdt_entry_t {
  uint16_t limit;
  uint16_t baseLow;
  uint8_t baseMid;
  uint8_t access;
  uint8_t granularity;
  uint8_t baseHigh;
} __attribute__((packed));