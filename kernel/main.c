#include <stddef.h>
#include <stdint.h>

#include "attributes.h"
#include "gdt.h"
#include "idt.h"
#include "vga.h"


#define HEXA "0123456789ABCDEF"


NORETURN
REGPARAM(2)
void kernel_main(uint32_t magic, UNUSED void* addr)
{
    setup_gdt();
    setup_idt();

    __asm__ volatile("int $0x00");

    char magic_str[9];

    for (int i = 0; i < 8; i++) {
        magic_str[7 - i] = HEXA[(magic >> (i * 4)) & 0xF];
    }
    magic_str[8] = '\0';

    vga_write(magic_str, 0);

    while (1) {
        __asm__ volatile("hlt");
    }
}