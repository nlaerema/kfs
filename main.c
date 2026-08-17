#include "vga.h"

static void vga_write(const char *str)
{
    for (size_t i = 0; str[i] != '\0'; i++) {
        VGA_TEXT_BUFFER[i] = (uint16_t)str[i] | 0x0F00;
    }
}


[[noreturn]]
void kernel_main(void)
{
    vga_write("Hello, World !");

    while (1) {
        __asm__ __volatile__("hlt");
    }
}