#include <kernel/drivers/screen.hpp>

void test() {
  volatile uint16_t* vga_buffer = (uint16_t*)0xb8000;
  vga_buffer[0] = VGA_COLOR('X', VGA_GREEN);
}
