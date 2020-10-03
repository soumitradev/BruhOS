#pragma once

#include <stdint.h>
#include <kernel/cpu/reg.hpp>
#include <kernel/cpu/isr.hpp>

void timer_handler(registers_t *r);
void set_pit_freq(uint64_t freq);
void wait(uint64_t ticks);

extern volatile uint64_t global_tick;
