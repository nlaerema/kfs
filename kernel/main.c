#include "gdt.h"
#include "idt.h"
#include "halt.h"

#include "drivers/vga.h"

#include "lib/attributes.h"
#include "lib/multiboot2.h"
#include "lib/macros.h"

#include <stddef.h>
#include <stdint.h>


NORETURN
void kernel_main(multiboot_bootloader_magic_t magic, UNUSED const multiboot_info_t* mbi)
{
    setup_gdt();
    setup_idt();

    if (magic != MULTIBOOT2_BOOTLOADER_MAGIC) {
        vga_printf("Invalid bootloader magic: 0x%X\n", magic);
        halt();
    }

    unsigned int i = 0;
    unsigned int op = 0;
    while (true) {
        if (op % 100000000 == 0) {
            vga_printf(ESC"F%xB0K%x;Counter: %u\n", i % 16, i % 2, i);
            if (i % 21 == 0) {
                vga_scroll();
                vga_scroll();
                vga_scroll();
                vga_scroll();
                vga_scroll();
                vga_scroll();
                vga_scroll();
                vga_scroll();
            }
            if (i % 42 == 0) {
                i /= i - 42;    
            }
            i++;
        }
        op++;
    }

    halt();
}