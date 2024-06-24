.PHONY: all clean build user
all: build

LOG ?= error

SRC_DIR = src

TOOLPREFIX = riscv64-unknown-elf-
CC = $(TOOLPREFIX)gcc
AS = $(TOOLPREFIX)gcc
LD = $(TOOLPREFIX)ld
OBJCOPY = $(TOOLPREFIX)objcopy
OBJDUMP = $(TOOLPREFIX)objdump
PY = python3
GDB = $(TOOLPREFIX)gdb
CP = cp
BUILDDIR = build

AS_SRCS = $(wildcard $(SRC_DIR)/*.S)
C_SRCS = $(wildcard $(SRC_DIR)/*.c)

AS_OBJS = $(addprefix $(BUILDDIR)/, $(addsuffix .o, $(basename $(AS_SRCS))))
C_OBJS = $(addprefix $(BUILDDIR)/, $(addsuffix .o, $(basename $(C_SRCS))))

OBJS = $(C_OBJS) $(AS_OBJS)

CFLAGS = -Wall -Werror -O -fno-omit-frame-pointer -ggdb
CFLAGS += -MD
CFLAGS += -mcmodel=medany
CFLAGS += -ffreestanding -fno-common -nostdlib -mno-relax
CFLAGS += -I$(SRC_DIR)
CFLAGS += $(shell $(CC) -fno-stack-protector -E -x c /dev/null >/dev/null 2>&1 && echo -fno-stack-protector)

$(AS_OBJS): $(BUILDDIR)/$(SRC_DIR)/%.o : $(SRC_DIR)/%.S
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

$(C_OBJS): $(BUILDDIR)/$(SRC_DIR)/%.o : $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

build: build_kernel

build_kernel: $(OBJS)
	$(LD) $(LDFLAGS) -T $(SRC_DIR)/kernel.ld -o $(BUILDDIR)/kernel $(OBJS)

clean:
	rm -rf $(BUILDDIR)

BOARD		?= qemu
SBI			?= rustsbi
BOOTLOADER	:= /workspace/rCore/rCore/bootloader/rustsbi-qemu.bin

QEMU = qemu-system-riscv64
QEMUOPTS = \
	-nographic \
	-machine virt \
	-bios $(BOOTLOADER) \
	-device loader,file=build/kernel,addr=0x80200000 

run: build
	$(QEMU) $(QEMUOPTS)