
CFILES    := $(shell find src/ -type f -name '*.cpp')
CC         = g++
LD         = ld
OBJ       := $(CFILES:.cpp=.o)
KERNEL_HDD = build/disk.hdd
KERNEL_ELF = kernel.elf

CHARDFLAGS := $(CFLAGS)            \
	-DBUILD_TIME='"$(BUILD_TIME)"' \
	-std=c++17                     \
	-masm=intel                    \
	-fno-pic                       \
	-mno-sse                       \
	-mno-sse2                      \
	-mno-mmx                       \
	-mno-80387                     \
	-mno-red-zone                  \
	-mcmodel=kernel                \
	-ffreestanding                 \
	-fno-stack-protector           \
	-fno-omit-frame-pointer        \
	-Isrc/                         \

LDHARDFLAGS := $(LDFLAGS)     \
	-nostdlib                 \
	-no-pie                   \
	-z max-page-size=0x1000   \
	-T src/linker.ld

.PHONY: clean
.DEFAULT_GOAL = $(KERNEL_HDD)

disk: $(KERNEL_HDD)
run: $(KERNEL_HDD)
	qemu-system-x86_64 -m 2G -hda $(KERNEL_HDD)

%.o: %.cpp
	$(CC) $(CHARDFLAGS) -c $< -o $@

$(KERNEL_ELF): $(OBJ)
	$(LD) $(LDHARDFLAGS) $(OBJ) -o $@

limine/limine-install:
	$(MAKE) -C limine/ limine-install

$(KERNEL_HDD): $(KERNEL_ELF) limine/limine-install
	-mkdir -p build
	dd if=/dev/zero bs=1M count=0 seek=64 of=$(KERNEL_HDD)
	parted -s $(KERNEL_HDD) mklabel msdos
	parted -s $(KERNEL_HDD) mkpart primary 1 100%
	echfs-utils -m -p0 $(KERNEL_HDD) quick-format 32768
	echfs-utils -m -p0 $(KERNEL_HDD) import $(KERNEL_ELF) $(KERNEL_ELF)
	echfs-utils -m -p0 $(KERNEL_HDD) import limine.cfg limine.cfg
	limine/limine-install limine/limine.bin $(KERNEL_HDD)

clean:
	-rm -rf $(KERNEL_HDD) $(KERNEL_ELF) $(OBJ) build