#include <stddef.h>
#include <stdint.h>

#include "attributes.h"
#include "multiboot2.h"
#include "gdt.h"
#include "idt.h"
#include "vga.h"


#define HEXA "0123456789ABCDEF"


NORETURN
REGPARAM(2)
void kernel_main(multiboot_bootloader_magic_t magic, UNUSED const multiboot_info_t* mbi)
{
    setup_gdt();
    setup_idt();

    __asm__ volatile("int $0x00");

    if (magic != MULTIBOOT2_BOOTLOADER_MAGIC) {
        vga_write("FAILED", 0);
    } else {
        vga_write("SUCCESS", 0);
    }

    while (1) {
        __asm__ volatile("hlt");
    }
}