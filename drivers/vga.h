#pragma once

#include "lib/attributes.h"

#include <stddef.h>
#include <stdint.h>

typedef enum : uint8_t {
    VGA_BLACK         = 0x0,
    VGA_BLUE          = 0x1,
    VGA_GREEN         = 0x2,
    VGA_CYAN          = 0x3,
    VGA_RED           = 0x4,
    VGA_MAGENTA       = 0x5,
    VGA_BROWN         = 0x6,
    VGA_LIGHT_GRAY    = 0x7,
    VGA_DARK_GRAY     = 0x8,
    VGA_LIGHT_BLUE    = 0x9,
    VGA_LIGHT_GREEN   = 0xA,
    VGA_LIGHT_CYAN    = 0xB,
    VGA_LIGHT_RED     = 0xC,
    VGA_LIGHT_MAGENTA = 0xD,
    VGA_YELLOW        = 0xE,
    VGA_WHITE         = 0xF,
} vga_color_t;

PRESERVE_ALL_REGS
void vga_scroll(void);

PRESERVE_ALL_REGS
void vga_put(char c);

PRESERVE_ALL_REGS
void vga_write(const void* data, size_t size);

size_t vga_printf(const char* format, ...);