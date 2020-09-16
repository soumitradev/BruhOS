#include <kernel/boot/stivale.hpp>
#include <kernel/drivers/screen.hpp>

static char stack[4096] = {0};

__attribute__((section(".stivalehdr"), used)) struct stivale_header header = {
    .stack = (uintptr_t)stack + sizeof(stack),
    .flags = 0,
    .framebuffer_width = 0,
    .framebuffer_height = 0,
    .framebuffer_bpp = 0,
    .entry_point = 0};

extern "C" void kmain(struct stivale_struct* bootloader_data) {
  gdt.gdtInit();
  asm volatile("hlt");
}