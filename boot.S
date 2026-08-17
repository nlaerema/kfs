#include "multiboot.h"

#define BOOT_STACK_SIZE 16384

.intel_syntax


.section .multiboot, "a", @progbits

.long MULTIBOOT_MAGIC
.long MULTIBOOT_FLAGS
.long MULTIBOOT_CHECKSUM


.section .boot_stack, "aw", @nobits

.global boot_stack_bottom
boot_stack_bottom:

    .skip BOOT_STACK_SIZE

.global boot_stack_top
boot_stack_top:


.text

.global _start
.type _start, @function
_start:
    mov esp, offset boot_stack_top
    jmp kernel_main
