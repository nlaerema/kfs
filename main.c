#include <stddef.h>
#include <stdint.h>

#include "macro.h"
#include "multiboot.h"
#include "vga.h"

#define BOOT_STACK_SIZE 16384

SECTION(".multiboot")
const multiboot_header_t multiboot_header = MULTIBOOT_HEADER(0);

SECTION(".boot_stack")
uint8_t boot_stack[BOOT_STACK_SIZE];

void NORETURN kernel_main(void) {
  vga_write("Hello, World !");

  while (1) {
    asm volatile("hlt");
  }
}