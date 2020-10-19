#include <kernel/boot/stivale.hpp>
#include <kernel/drivers/screen.hpp>
#include <kernel/mm/mm.hpp>
#include <kernel/mm/pmm.hpp>
#include <lib/bitshit.hpp>
#include <lib/memutils.hpp>
#include <lib/strutils.hpp>

static BitMap page_bmp(0, 0);
static uint64_t detected_memory = 0;

void init_pmm(stivale_struct *boot_info) {
  stivale_mmap_entry_t *stivale_mmap_entry =
      (stivale_mmap_entry_t *)boot_info->memory_map_addr;
  for (uint64_t i = 0; i < boot_info->memory_map_entries; i++) {
    // God I really need a printf
    print("[PMM] ", VGA_COLOR(VGA_BLACK, VGA_LIGHT_GREEN));
    print("[0x");
    print(itob(stivale_mmap_entry[i].addr, 16));
    print(" - 0x");
    print(itob(stivale_mmap_entry[i].addr + stivale_mmap_entry[i].len, 16));
    print("]: size 0x");
    print(itob(stivale_mmap_entry[i].len, 16));
    print(", type 0x");
    print(itob(stivale_mmap_entry[i].type, 16));
    print("\n");

    detected_memory += stivale_mmap_entry[i].len;
  }
  print("[PMM] ", VGA_COLOR(VGA_BLACK, VGA_LIGHT_GREEN));
  print("Total detected memory: 0x");
  print(itob(detected_memory, 16));
  print("\n");

  uint64_t bmp_size = ((detected_memory / 4096) / 8);
  uint64_t bmp_base = 0;

  print("[PMM] ", VGA_COLOR(VGA_BLACK, VGA_LIGHT_GREEN));
  print("Planned pages: ");
  print(itob(bmp_size, 10));
  print("\n");

  for (uint64_t i = 0; i < boot_info->memory_map_entries; i++) {
    if ((stivale_mmap_entry[i].type == 0x1) &&
        (stivale_mmap_entry[i].len >= bmp_size)) {
      page_bmp.bitmap_base =
          (uint8_t *)(stivale_mmap_entry[i].addr + KERNEL_VIRT_ADDR_BASE);
      ;
      page_bmp.size = bmp_size;
      bmp_base = stivale_mmap_entry[i].addr;
      memory_set((uint64_t *)page_bmp.bitmap_base, 0xffffffffffffffff,
                 bmp_size / 8);
      break;
    }
  }

  for (uint64_t i = 0; i < boot_info->memory_map_entries; i++) {
    if (stivale_mmap_entry[i].type == 1) {
      free_mem(stivale_mmap_entry[i].addr, stivale_mmap_entry[i].len);
    }
  }

  reserve_mem(bmp_base, bmp_size);
  reserve_mem(0, 0x100000);

  print("[PMM] ", VGA_COLOR(VGA_BLACK, VGA_LIGHT_GREEN));
  print("PMM initialized.");
  print("\n");
}

static void free_mem(uint64_t base_addr, uint64_t size) {
  for (uint64_t i = base_addr / PAGE_SIZE;
       i < ((base_addr + size) / PAGE_SIZE + (size % PAGE_SIZE ? 1 : 0)); i++) {
    page_bmp.clr_bit(i);
  }
}

static void reserve_mem(uint64_t base_addr, uint64_t size) {
  for (uint64_t i = base_addr / PAGE_SIZE;
       i < ((base_addr + size) / PAGE_SIZE + (size % PAGE_SIZE ? 1 : 0)); i++) {
    page_bmp.set_bit(i);
  }
}

uint64_t alloc_pages(uint64_t number_pages) {
  uint64_t first_free_pg = first_free();
  uint64_t base_addr = first_free_pg * PAGE_SIZE;
  uint64_t cur_free = 0;

  if (first_free_pg == -1) {
    print("\n[PMM] ", VGA_COLOR(VGA_BLACK, VGA_RED));
    print("Error: No free pages!");
    return -1;
  }

  for (uint64_t i = first_free_pg; i < page_bmp.size; i++) {
    if (page_bmp.get_bit(i)) {
      base_addr += (cur_free + 1) * PAGE_SIZE;
      cur_free = 0;
      continue;
      // cur_free = 0;
      // i = first_free_after(i);
      // first_free_pg = i;
    }

    if (++cur_free == number_pages) {
      for (uint64_t j = 0; j < number_pages; j++) {
        page_bmp.set_bit(j + base_addr / PAGE_SIZE);
      }
      return base_addr;
    }
  }

  return 0;
}

void free_pages(uint64_t *addr, uint64_t number_pages) {
  uint64_t start_page = (uint64_t)addr / PAGE_SIZE;
  for (uint64_t i = start_page; i < start_page + number_pages; i++) {
    page_bmp.clr_bit(i);
  }
}

uint64_t locate_alloc(uint64_t number_pages) {
  uint64_t base_addr = alloc_pages(number_pages);
  memory_set((uint64_t *)base_addr + KERNEL_VIRT_ADDR_BASE, (uint64_t)0,
             number_pages * 0x1000);
  return base_addr;
}

static uint64_t first_free_after(uint64_t low_limit) {
  for (uint64_t i = low_limit; i < page_bmp.size; i++) {
    if (!page_bmp.get_bit(i)) {
      return i;
    }
  }
  return -1;
}

static uint64_t first_free() {
  for (uint64_t i = 0; i < page_bmp.size; i++) {
    if (!page_bmp.get_bit(i)) {
      return i;
    }
  }
  return -1;
}