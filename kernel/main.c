#include "gdt.h"
#include "idt.h"

#include "drivers/vga.h"

#include "lib/attributes.h"
#include "lib/multiboot2.h"
#include "lib/macros.h"

#include <stddef.h>
#include <stdint.h>


#define HEXA "0123456789ABCDEF"


NORETURN
void halt(void)
{
    while (true) {
        __asm__ volatile("hlt");
    }
}

NORETURN
void kernel_main(multiboot_bootloader_magic_t magic, UNUSED const multiboot_info_t* mbi)
{
    setup_gdt();
    setup_idt();

//    __asm__ volatile("int $0x00");

    if (magic != MULTIBOOT2_BOOTLOADER_MAGIC) {
        vga_printf("Invalid bootloader magic: 0x%X\n", magic);
        halt();
    }

    unsigned int i = 0;
    unsigned int op = 0;
    while (true) {
        if (op % 100000000 == 0) {
            char f = HEXA[(i % 16)];
            char b = HEXA[((i + 3) % 16)];
            char k = HEXA[(i % 2)];
            vga_printf(ESC"F%cB%cK%c;Counter: %u\n", f, b, k, i);
            if (i % 25 == 0) {
                vga_scroll();
                vga_scroll();
                vga_scroll();
                vga_scroll();
                vga_scroll();
                vga_scroll();
                vga_scroll();
                vga_scroll();
            }
            i ++;
        }
        op++;
    }

    halt();
}