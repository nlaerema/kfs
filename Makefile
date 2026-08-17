NAME      := kfs

ISO       := $(NAME).iso
KERNEL    := $(NAME).elf

CC        := clang
AS        := clang
LD        := ld.lld

TARGET    := i386-elf
LINKER    := linker.ld

SRCS_C    := main.c
SRCS_S    := boot.S

BUILD_DIR := build

OBJS_C    := $(addprefix $(BUILD_DIR)/,$(SRCS_C:.c=.o))
OBJS_S    := $(addprefix $(BUILD_DIR)/,$(SRCS_S:.S=.o))
OBJS      := $(OBJS_S) $(OBJS_C)

CFLAGS    := -target $(TARGET) \
             -ffreestanding \
             -fno-builtin \
             -fno-stack-protector \
             -nostdlib \
             -Wall -Wextra

ASFLAGS   := -target $(TARGET)

LDFLAGS   := -m elf_i386 -T $(LINKER)


.PHONY: all
all: $(BUILD_DIR)/$(KERNEL)

$(BUILD_DIR)/$(KERNEL): $(OBJS)
	$(LD) $(LDFLAGS) -o $@ $(OBJS)

$(BUILD_DIR)/%.o: %.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: %.S | $(BUILD_DIR)
	$(AS) $(ASFLAGS) -c $< -o $@

$(BUILD_DIR):
	mkdir -p $@


.PHONY: iso
iso: $(BUILD_DIR)/$(ISO)

$(BUILD_DIR)/$(ISO): $(BUILD_DIR)/$(KERNEL)
	mkdir -p $(BUILD_DIR)/iso/boot/grub
	cp $(BUILD_DIR)/$(KERNEL) $(BUILD_DIR)/iso/boot/$(KERNEL)
	NAME=$(NAME) KERNEL=$(KERNEL) tera -f grub.cfg.tera --env > $(BUILD_DIR)/iso/boot/grub/grub.cfg
	grub-mkrescue -o $@ $(BUILD_DIR)/iso

.PHONY: run
run: iso
	qemu-system-i386 -cdrom $(BUILD_DIR)/$(ISO)


.PHONY: clean
clean:
	rm -f $(OBJS)

.PHONY: fclean
fclean: clean
	rm -rf $(BUILD_DIR)

.PHONY: re
re: fclean all