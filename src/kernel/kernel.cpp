#include <kernel/boot/stivale.hpp>
#include <kernel/drivers/screen.hpp>
#include <lib/strutils.hpp>
extern "C" void init_gdt();

static char stack[4096] = {0};

__attribute__((section(".stivalehdr"), used)) struct stivale_header header = {
  .stack = (uintptr_t)stack + sizeof(stack),
  .flags = 0,
  .framebuffer_width = 0,
  .framebuffer_height = 0,
  .framebuffer_bpp = 0,
  .entry_point = 0};

extern "C" void kmain(struct stivale_struct* bootloader_data) {
  init_gdt();
  asm volatile("int $3");
  print("BruhOS", VGA_COLOR(VGA_BLACK, VGA_GREEN));
  for (;;)
    ;
}