NAME      := kfs

ISO       := $(NAME).iso
KERNEL    := $(NAME).elf

CC        := clang
AS        := clang
LD        := ld.lld

TARGET    := i386-elf
LINKER    := linker.ld

SRCS_C    := $(wildcard boot/*.c kernel/*.c drivers/*.c lib/*.c)
SRCS_ASM  := $(wildcard boot/*.S kernel/*.S)

BUILD_DIR := build

OBJS_C    := $(addprefix $(BUILD_DIR)/, $(addsuffix .o, $(SRCS_C)))
OBJS_ASM  := $(addprefix $(BUILD_DIR)/, $(addsuffix .o, $(SRCS_ASM)))
OBJS      := $(OBJS_ASM) $(OBJS_C)

DEPS      := $(OBJS:.o=.d)

DEBUG ?= 0

CPPFLAGS  := -I. -Iinclude

CFLAGS    := -target $(TARGET) \
             -ffreestanding \
             -fno-builtin \
             -fno-stack-protector \
             -nostdlib \
             -Wall -Wextra \
             -MMD -MP \
			 -std=c23
ifeq ($(DEBUG), 1)
    CFLAGS += -g -O0
else
    CFLAGS += -O2
endif

ASFLAGS   := $(CFLAGS)

LDFLAGS   := -m elf_i386 -T $(LINKER)
ifeq ($(DEBUG), 0)
    LDFLAGS += --strip-all
endif

.DELETE_ON_ERROR:

.PHONY: all
all: $(BUILD_DIR)/$(KERNEL)

$(BUILD_DIR)/$(KERNEL): $(OBJS)
	$(LD) $(LDFLAGS) -o $@ $(OBJS)

$(BUILD_DIR)/%.c.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.S.o: %.S
	mkdir -p $(dir $@)
	$(AS) $(CPPFLAGS) $(ASFLAGS) -c $< -o $@

-include $(DEPS)

.PHONY: compiledb
compiledb:
	bear -- $(MAKE) re

.PHONY: iso
iso: $(BUILD_DIR)/$(ISO)

$(BUILD_DIR)/iso/boot/grub/grub.cfg: grub.cfg.j2
	mkdir -p $(dir $@)
	minijinja-cli --strict $< -D NAME=$(NAME) -D KERNEL=$(KERNEL) -o $@

$(BUILD_DIR)/$(ISO): $(BUILD_DIR)/$(KERNEL) $(BUILD_DIR)/iso/boot/grub/grub.cfg
	cp $(BUILD_DIR)/$(KERNEL) $(BUILD_DIR)/iso/boot/$(KERNEL)
	grub-mkrescue -o $@ $(BUILD_DIR)/iso

.PHONY: run
run: iso
	qemu-system-i386 -cdrom $(BUILD_DIR)/$(ISO)

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)

.PHONY: fclean
fclean: clean

.PHONY: re
re: fclean all