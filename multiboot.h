#pragma once

#include <stdint.h>

#include "macro.h"

#define MULTIBOOT_MAGIC 0x1BADB002

#define MULTIBOOT_HEADER(_flags) \
    ((multiboot_header_t) { \
        .magic = MULTIBOOT_MAGIC, \
        .flags = (_flags), \
        .checksum = -(MULTIBOOT_MAGIC + (_flags)) \
    })

typedef struct PACKED {
    uint32_t magic;
    uint32_t flags;
    uint32_t checksum;
} multiboot_header_t;