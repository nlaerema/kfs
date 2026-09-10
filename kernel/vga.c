#include <stdint.h>
#include <stddef.h>

#include "vga.h"


#define VGA_MEMORY ((volatile uint16_t *)0xB8000)
#define VGA_COLS 80
#define VGA_ROWS 25


NO_CALLER_SAVED_REGISTERS
void vga_write(const char* str, int line)
{
    for (size_t i = 0; str[i] != '\0'; i++) {
        VGA_MEMORY[line * VGA_COLS + i] = (uint16_t)str[i] | 0x0F00;
    }
}