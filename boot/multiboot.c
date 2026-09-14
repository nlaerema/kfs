#include "multiboot2.h"
#include "attributes.h"


typedef struct {
    multiboot_header_t header;
    multiboot_header_tag_t end;
} multiboot_t;


SECTION(".multiboot")
ALIGN(MULTIBOOT_HEADER_ALIGN)
const multiboot_t multiboot = {
    .header = MULTIBOOT_HEADER(MULTIBOOT_ARCHITECTURE_I386, sizeof(multiboot_t)),
    .end = MULTIBOOT_HEADER_TAG_END(),
};