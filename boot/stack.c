#include <stdint.h>

#include "attributes.h"


#define BOOT_STACK_ALIGN 8
#define BOOT_STACK_SIZE 16384


SECTION(".boot_stack")
ALIGN(BOOT_STACK_ALIGN)
uint8_t boot_stack[BOOT_STACK_SIZE];