#include "vga.h"

#include <stdint.h>
#include <stddef.h>

void vga_write(const char* str)
{
    for (size_t i = 0; str[i] != '\0'; i++) {
        VGA_MEMORY[i] = (uint16_t)str[i] | 0x0F00;
    }
}