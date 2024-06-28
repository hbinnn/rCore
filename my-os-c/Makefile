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

USER_SRC_DIR = user
USER_LIB_SRC_DIR = user/lib

USER_LIB_AS_SRCS = $(wildcard $(USER_LIB_SRC_DIR)/*.S)
USER_LIB_C_SRCS = $(wildcard $(USER_LIB_SRC_DIR)/*.c)

USER_LIB_AS_OBJS = $(addprefix $(BUILDDIR)/, $(addsuffix .o, $(basename $(USER_LIB_AS_SRCS))))
USER_LIB_C_OBJS = $(addprefix $(BUILDDIR)/, $(addsuffix .o, $(basename $(USER_LIB_C_SRCS))))

USER_LIB_OBJS = $(USER_LIB_AS_OBJS) $(USER_LIB_C_OBJS)

$(USER_LIB_AS_OBJS): $(BUILDDIR)/$(USER_LIB_SRC_DIR)/%.o : $(USER_LIB_SRC_DIR)/%.S
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

$(USER_LIB_C_OBJS): $(BUILDDIR)/$(USER_LIB_SRC_DIR)/%.o : $(USER_LIB_SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

HELLO_WORLD_DIR = $(USER_SRC_DIR)/hello_world

HELLO_WORLD_SRCS = $(wildcard $(HELLO_WORLD_DIR)/*.c)

HELLO_WORLD_OBJS = $(addprefix $(BUILDDIR)/, $(addsuffix .o, $(basename $(HELLO_WORLD_SRCS))))

$(HELLO_WORLD_OBJS): $(BUILDDIR)/$(HELLO_WORLD_DIR)/%.o : $(HELLO_WORLD_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

hello_world: $(USER_LIB_OBJS) $(HELLO_WORLD_OBJS)
	$(LD) $(LDFLAGS) -T $(USER_LIB_SRC_DIR)/user.ld -o $(BUILDDIR)/hello_world $(USER_LIB_OBJS) $(HELLO_WORLD_OBJS)

STORE_FAULT_DIR = $(USER_SRC_DIR)/store_fault

STORE_FAULT_SRCS = $(wildcard $(STORE_FAULT_DIR)/*.c)

STORE_FAULT_OBJS = $(addprefix $(BUILDDIR)/, $(addsuffix .o, $(basename $(STORE_FAULT_SRCS))))

$(STORE_FAULT_OBJS): $(BUILDDIR)/$(STORE_FAULT_DIR)/%.o : $(STORE_FAULT_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

store_fault: $(USER_LIB_OBJS) $(STORE_FAULT_OBJS)
	$(LD) $(LDFLAGS) -T $(USER_LIB_SRC_DIR)/user.ld -o $(BUILDDIR)/store_fault $(USER_LIB_OBJS) $(STORE_FAULT_OBJS)

POWER_DIR = $(USER_SRC_DIR)/power

POWER_SRCS = $(wildcard $(POWER_DIR)/*.c)

POWER_OBJS = $(addprefix $(BUILDDIR)/, $(addsuffix .o, $(basename $(POWER_SRCS))))

$(POWER_OBJS): $(BUILDDIR)/$(POWER_DIR)/%.o : $(POWER_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

power: $(USER_LIB_OBJS) $(POWER_OBJS)
	$(LD) $(LDFLAGS) -T $(USER_LIB_SRC_DIR)/user.ld -o $(BUILDDIR)/power $(USER_LIB_OBJS) $(POWER_OBJS)


user: hello_world store_fault power