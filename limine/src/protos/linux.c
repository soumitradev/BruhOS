#include <stdint.h>
#include <stddef.h>
#include <protos/linux.h>
#include <fs/file.h>
#include <lib/blib.h>
#include <lib/real.h>
#include <drivers/vga_textmode.h>
#include <lib/config.h>
#include <lib/print.h>
#include <lib/memmap.h>
#include <lib/asm.h>

#define KERNEL_LOAD_ADDR ((size_t)0x100000)
#define INITRD_LOAD_ADDR ((size_t)0x1000000)

void linux_load(char *cmdline, int boot_drive) {
    int kernel_drive; {
        char buf[32];
        if (!config_get_value(buf, 0, 32, "KERNEL_DRIVE")) {
            kernel_drive = boot_drive;
        } else {
            kernel_drive = (int)strtoui(buf);
        }
    }

    int kernel_part; {
        char buf[32];
        if (!config_get_value(buf, 0, 32, "KERNEL_PARTITION")) {
            panic("KERNEL_PARTITION not specified");
        } else {
            kernel_part = (int)strtoui(buf);
        }
    }

    char *kernel_path = balloc(128);
    if (!config_get_value(kernel_path, 0, 128, "KERNEL_PATH")) {
        panic("KERNEL_PATH not specified");
    }

    struct file_handle *fd = balloc(sizeof(struct file_handle));
    if (fopen(fd, kernel_drive, kernel_part, kernel_path)) {
        panic("Could not open kernel file");
    }

    uint32_t signature;
    fread(fd, &signature, 0x202, sizeof(uint32_t));

    // validate signature
    if (signature != 0x53726448) {
        panic("Invalid Linux kernel signature");
    }

    size_t setup_code_size = 0;
    fread(fd, &setup_code_size, 0x1f1, 1);

    if (setup_code_size == 0)
        setup_code_size = 4;

    setup_code_size *= 512;

    print("linux: Setup code size: %x\n", setup_code_size);

    size_t real_mode_code_size = 512 + setup_code_size;

    print("linux: Real Mode code size: %x\n", real_mode_code_size);

    void *real_mode_code = balloc_aligned(real_mode_code_size, 0x1000);

    fread(fd, real_mode_code, 0, real_mode_code_size);

    size_t heap_end_ptr = ((real_mode_code_size & 0x0f) + 0x10) - 0x200;
    *((uint16_t *)(real_mode_code + 0x224)) = (uint16_t)heap_end_ptr;

    // vid_mode. 0xffff means "normal"
    *((uint16_t *)(real_mode_code + 0x1fa)) = 0xffff;

    uint16_t boot_protocol_ver;
    boot_protocol_ver = *((uint16_t *)(real_mode_code + 0x206));

    print("linux: Boot protocol: %u.%u\n",
          boot_protocol_ver >> 8, boot_protocol_ver & 0xff);

    char *kernel_version;
    kernel_version = real_mode_code + *((uint16_t *)(real_mode_code + 0x20e)) + 0x200;

    if (kernel_version) {
        print("linux: Kernel version: %s\n", kernel_version);
    }

    // set type of loader
    *((uint8_t *)(real_mode_code + 0x210)) = 0xff;

    uint8_t loadflags;
    loadflags = *((uint8_t *)(real_mode_code + 0x211));

    loadflags |=  (1 << 0);     // kernel is loaded at 0x100000
    loadflags &= ~(1 << 5);     // print early messages
    loadflags |=  (1 << 7);     // can use heap

    *((uint8_t *)(real_mode_code + 0x211)) = loadflags;

    // cmdline
    *((uint32_t *)(real_mode_code + 0x228)) = (uint32_t)cmdline;

    // load kernel
    print("Loading kernel...\n");
    memmap_alloc_range(KERNEL_LOAD_ADDR, fd->size - real_mode_code_size, 0);
    fread(fd, (void *)KERNEL_LOAD_ADDR, real_mode_code_size, fd->size - real_mode_code_size);

    char initrd_path[64];
    if (!config_get_value(initrd_path, 0, 64, "INITRD_PATH"))
        panic("INITRD_PATH not specified");

    int initrd_part; {
        char buf[32];
        if (!config_get_value(buf, 0, 32, "INITRD_PARTITION")) {
            initrd_part = fd->partition;
        } else {
            initrd_part = (int)strtoui(buf);
        }
    }

    struct file_handle initrd;
    if (fopen(&initrd, fd->disk, initrd_part, initrd_path)) {
        panic("Failed to open initrd");
    }

    print("Loading initrd...\n");
    memmap_alloc_range(INITRD_LOAD_ADDR, initrd.size, 0);
    fread(&initrd, (void *)INITRD_LOAD_ADDR, 0, initrd.size);

    *((uint32_t *)(real_mode_code + 0x218)) = (uint32_t)INITRD_LOAD_ADDR;
    *((uint32_t *)(real_mode_code + 0x21c)) = (uint32_t)initrd.size;

    uint16_t real_mode_code_seg = rm_seg(real_mode_code);
    uint16_t kernel_entry_seg   = real_mode_code_seg + 0x20;

    deinit_vga_textmode();

    ASM(
        "cli\n\t"
        "cld\n\t"

        FARJMP32("0x08", "1f")
        "1: .code16\n\t"
        "mov ax, 0x10\n\t"
        "mov ds, ax\n\t"
        "mov es, ax\n\t"
        "mov fs, ax\n\t"
        "mov gs, ax\n\t"
        "mov ss, ax\n\t"
        "mov eax, cr0\n\t"
        "and al, 0xfe\n\t"
        "mov cr0, eax\n\t"
        FARJMP16("0", "1f")
        "1:\n\t"
        "mov ds, bx\n\t"
        "mov es, bx\n\t"
        "mov fs, bx\n\t"
        "mov gs, bx\n\t"
        "mov ss, bx\n\t"

        "mov sp, 0xfdf0\n\t"

        "push cx\n\t"
        "push 0\n\t"
        "retf\n\t",
        : "b" (real_mode_code_seg), "c" (kernel_entry_seg)
        : "memory"
    );
}
