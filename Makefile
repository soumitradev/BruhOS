
CXXFILES  := $(shell find src/ -type f -name '*.cpp')
CXXC       = ~/.local/bin/cross_compiler/x86_64/bin/x86_64-elf-g++
LD         = ~/.local/bin/cross_compiler/x86_64/bin/x86_64-elf-ld
OBJ       := $(CXXFILES:.cpp=.o)
KERNEL_HDD = build/disk.hdd
KERNEL_ELF = kernel.elf

CXXHARDFLAGS := $(CXXFLAGS)      \
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
	-I src/                        \

LDHARDFLAGS := $(LDFLAGS)   \
	-nostdlib                 \
	-no-pie                   \
	-z max-page-size=0x1000   \
	-T src/linker.ld

.PHONY: clean
.DEFAULT_GOAL = $(KERNEL_HDD)

disk: $(KERNEL_HDD)
run: $(KERNEL_HDD)
	qemu-system-x86_64 -m 2G -drive format=raw,media=disk,index=0,file=$(KERNEL_HDD)

%.o: %.cpp
	$(CXXC) $(CXXHARDFLAGS) -c $< -o $@

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