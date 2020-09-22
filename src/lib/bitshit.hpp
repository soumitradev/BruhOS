#pragma once

#include <stdint.h>

#define low_16(address) (uint16_t)((address)&0xFFFF)
#define high_16(address) (uint16_t)((address >> 16) & 0xFFFF)
#define low_32(address) (uint16_t)((address)&0xFFFFFFFF)
#define high_32(address) (uint16_t)((address >> 32) & 0xFFFFFFFF)
