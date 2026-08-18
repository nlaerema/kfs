#pragma once

#include <stdint.h>

#define VGA_MEMORY ((volatile uint16_t *)0xB8000)
#define VGA_COLS 80
#define VGA_ROWS 25

void vga_write(const char *str);