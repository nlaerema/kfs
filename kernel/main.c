#include <stddef.h>
#include <stdint.h>

#include "attributes.h"
#include "vga.h"

NORETURN
void kernel_main(void)
{
    vga_write("Hello, World !");

    while (1) {
        asm("hlt");
    }
}