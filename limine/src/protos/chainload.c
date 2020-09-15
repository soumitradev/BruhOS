#include <stddef.h>
#include <stdint.h>
#include <protos/chainload.h>
#include <lib/part.h>
#include <lib/config.h>
#include <lib/blib.h>
#include <drivers/disk.h>
#include <drivers/vga_textmode.h>
#include <lib/asm.h>

void chainload(void) {
    int part; {
        char buf[32];
        if (!config_get_value(buf, 0, 32, "PARTITION")) {
            part = -1;
        } else {
            part = (int)strtoui(buf);
        }
    }
    int drive; {
        char buf[32];
        if (!config_get_value(buf, 0, 32, "DRIVE")) {
            panic("DRIVE not specified");
        }
        drive = (int)strtoui(buf);
    }

    deinit_vga_textmode();

    if (part != -1) {
        struct part p;
        get_part(&p, drive, part);

        read_partition(drive, &p, (void *)0x7c00, 0, 512);
    } else {
        read(drive, (void *)0x7c00, 0, 512);
    }

    ASM(
        // Jump to real mode
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
        "mov ax, 0\n\t"
        "mov ds, ax\n\t"
        "mov es, ax\n\t"
        "mov fs, ax\n\t"
        "mov gs, ax\n\t"
        "mov ss, ax\n\t"
        "push 0\n\t"
        "push 0x7c00\n\t"
        "retf\n\t"
        ".code32\n\t",
        : "d" (drive)
        : "memory"
    );
}
