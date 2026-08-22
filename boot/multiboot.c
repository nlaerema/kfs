#include "multiboot2.h"
#include "attributes.h"

#define HEADER(_architecture, _header_length) \
(struct multiboot_header) { \
    .magic = MULTIBOOT2_HEADER_MAGIC, \
    .architecture = (_architecture), \
    .header_length = (_header_length), \
    .checksum = -(MULTIBOOT2_HEADER_MAGIC + (_architecture) + (_header_length)), \
}

#define END_TAG() \
(struct multiboot_header_tag) { \
    .type = MULTIBOOT_HEADER_TAG_END, \
    .flags = 0, \
    .size = sizeof(struct multiboot_header_tag), \
}


typedef struct {
    struct multiboot_header header;
    struct multiboot_header_tag end;
} multiboot_t;


SECTION(".multiboot")
ALIGN(MULTIBOOT_HEADER_ALIGN)
const multiboot_t multiboot = {
    .header = HEADER(MULTIBOOT_ARCHITECTURE_I386, sizeof(multiboot_t)),
    .end = END_TAG(),
};