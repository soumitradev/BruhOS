#include <kernel/boot/stivale.hpp>
#include <kernel/cpu/isr.hpp>
#include <kernel/cpu/pit.hpp>
#include <kernel/cpu/ports.hpp>
#include <kernel/drivers/screen.hpp>
#include <kernel/mm/pmm.hpp>
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
  clr_scr();
  init_gdt();
  print("[KERNEL] ", VGA_COLOR(VGA_BLACK, VGA_LIGHT_RED));
  print("GDT Loaded.\n");

  isr_install();
  asm volatile("sti");
  set_pit_freq(1000);
  print("[CPU] ", VGA_COLOR(VGA_BLACK, VGA_LIGHT_RED));
  print("Interrupts ready.\n");

  init_pmm(bootloader_data);
  print("[KMM] ", VGA_COLOR(VGA_BLACK, VGA_LIGHT_RED));
  print("PMM ready.\n");
  print(">");

  // print("BruhOS\n", VGA_COLOR(VGA_BLACK, VGA_GREEN));
  // print("| Version: 0.0.1a\n", VGA_COLOR(VGA_BLACK, VGA_WHITE));
  // print("| Arch: x86_64\n", VGA_COLOR(VGA_BLACK, VGA_WHITE));
  // print("| Resolution: 80x25\n", VGA_COLOR(VGA_BLACK, VGA_WHITE));
  for (;;) {
    asm volatile("hlt");
  }
}
