NAME      := kfs

ISO       := $(NAME).iso
KERNEL    := $(NAME).elf

CC        := clang
AS        := clang
LD        := ld.lld

TARGET    := i386-elf
LINKER    := linker.ld

SRCS_C    := $(wildcard boot/*.c kernel/*.c drivers/*.c lib/*.c)
SRCS_AS   := $(wildcard boot/*.s kernel/*.s lib/*.s)

BUILD_DIR := build
ISO_DIR   := $(BUILD_DIR)/iso

OBJS_C    := $(addprefix $(BUILD_DIR)/, $(addsuffix .o, $(SRCS_C)))
OBJS_AS   := $(addprefix $(BUILD_DIR)/, $(addsuffix .o, $(SRCS_AS)))
OBJS      := $(OBJS_AS) $(OBJS_C)

DEPS      := $(OBJS:.o=.d)

DEBUG ?= 0

INCLUDES  := -I.

CFLAGS    := -target $(TARGET) \
			 -ffreestanding \
			 -fno-stack-protector \
			 -mregparm=3 \
			 -Wall -Wextra \
			 -MMD -MP \
			 -std=c23
ifeq ($(DEBUG), 1)
	CFLAGS += -g -O0
else
	CFLAGS += -O2
endif

ASFLAGS   := -target $(TARGET)

LDFLAGS   := -m elf_i386 -T $(LINKER)
ifeq ($(DEBUG), 0)
	LDFLAGS += --strip-all
endif

GRUB_PLATFORM := i386-pc
GRUB_DIR      := /usr/lib/grub/$(GRUB_PLATFORM)

GRUB_FLAGS    := --directory=$(GRUB_DIR) \
            	 --compress=xz \
            	 --locales= \
            	 --fonts= \
            	 --themes=


.DELETE_ON_ERROR:

.PHONY: all
all: $(BUILD_DIR)/$(KERNEL) 

$(BUILD_DIR)/$(KERNEL): $(OBJS) $(LINKER)
	$(LD) $(LDFLAGS) -o $@ $(OBJS)

$(BUILD_DIR)/%.c.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(INCLUDES) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.s.o: %.s
	mkdir -p $(dir $@)
	$(AS) $(INCLUDES) $(ASFLAGS) -c $< -o $@

-include $(DEPS)

.PHONY: run
run: iso
	qemu-system-i386 -cdrom $(BUILD_DIR)/$(ISO)

.PHONY: iso
iso: $(BUILD_DIR)/$(ISO)

$(BUILD_DIR)/$(ISO): \
	$(BUILD_DIR)/$(KERNEL) \
	$(ISO_DIR)/boot/grub/grub.cfg
	cp $(BUILD_DIR)/$(KERNEL) $(ISO_DIR)/boot/$(KERNEL)
	grub-mkrescue $(GRUB_FLAGS) -o $@ $(ISO_DIR)
	ls -lh $@

$(ISO_DIR)/boot/grub/grub.cfg: grub.cfg.j2
	mkdir -p $(dir $@)
	minijinja-cli --strict $< \
		-D NAME=$(NAME) \
		-D KERNEL=$(KERNEL) \
		-o $@

.PHONY: compiledb
compiledb:
	bear -- $(MAKE) re

.PHONY: re
re: fclean
	$(MAKE) all
	
.PHONY: fclean
fclean: clean

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)