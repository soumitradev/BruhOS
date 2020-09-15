#include "./stivale.h"

#define VGA_ADDRESS 0xb8000
#define VGA_COLOR(character, color) \
  ((uint16_t)(character) | (uint16_t)(color) << 8)
#define VGA_BLACK 0
#define VGA_BLUE 1
#define VGA_GREEN 2
#define VGA_CYAN 3
#define VGA_RED 4
#define VGA_PURPLE 5
#define VGA_BROWN 6
#define VGA_GRAY 7
#define VGA_DARK_GRAY 8
#define VGA_LIGHT_BLUE 9
#define VGA_LIGHT_GREEN 10
#define VGA_LIGHT_CYAN 11
#define VGA_LIGHT_RED 12
#define VGA_LIGHT_PURPLE 13
#define VGA_YELLOW 14
#define VGA_WHITE 15

/**
 * Stack for bootstrapping the kernel
 */
static char stack[4096] = {0};

__attribute__((section(".stivalehdr"), used)) struct stivale_header header = {
  .stack = (uintptr_t)stack + sizeof(stack),
  .flags = 0,
  .framebuffer_width = 0,
  .framebuffer_height = 0,
  .framebuffer_bpp = 0,
  .entry_point = 0};

extern "C" void kmain(struct stivale_struct* bootloader_data) {
  volatile uint16_t* vga_buffer = (uint16_t*)0xb8000;
  vga_buffer[0] = VGA_COLOR('X', VGA_GREEN);
  asm volatile("hlt");
}