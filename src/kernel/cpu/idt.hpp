#pragma once

#include <stdint.h>

#define KERNEL_CS 0x08

// Structure of an idt gate
typedef struct {
  uint16_t low_offset;
  uint16_t sel;
  uint8_t always0;

  uint8_t flags;
  uint16_t mid_offset;
  uint32_t high_offset;
  uint32_t always0again;
} __attribute__((packed)) idt_gate_t;

// Structure of an idt entry
typedef struct {
  uint16_t limit;
  uint64_t base;
} __attribute__((packed)) idt_register_t;

// Create the idt
#define IDT_ENTRIES 256

// Functions
void set_idt_gate(int n, uint64_t handler);
void set_idt();
