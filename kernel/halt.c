#include "halt.h"

#include "drivers/vga.h"

#include "lib/attributes.h"
#include "lib/macros.h"

#include <stdarg.h>


#define HALT_MSG ESC"FfB0K0;Kernel halted\n"


NORETURN
PRESERVE_ALL_REGS
void halt(void)
{
    vga_write(HALT_MSG, sizeof(HALT_MSG) - 1);

    while (true) {
        __asm__ volatile("hlt");
    }
}