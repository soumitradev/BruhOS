#pragma once

#include <kernel/boot/stivale.hpp>
#include <lib/bitshit.hpp>

void init_pmm(struct stivale_struct *boot_info);

static void free_mem(uint64_t base_addr, uint64_t size);
static void reserve_mem(uint64_t base_addr, uint64_t size);

uint64_t alloc_pages(uint64_t number_pages);
void free_pages(uint64_t *addr, uint64_t number_pages);
uint64_t locate_alloc(uint64_t number_pages);
static uint64_t first_free_after(uint64_t low_limit);
static uint64_t first_free();