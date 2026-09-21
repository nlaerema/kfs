#include "idt.h"
#include "halt.h"

#include "drivers/vga.h"

#include "lib/i386/descriptor_table.h"
#include "lib/attributes.h"
#include "lib/macros.h"


#define IDT_COUNT 256
#define IDT_ALIGN 8

#define DIVIDE_ERROR_MESSAGE ESC"FcB0K0;Divide error\n"


void load_idt(const i386_descriptor_table_register_t* idt_register);


typedef struct {
    uint32_t eip;
    uint32_t cs;
    uint32_t eflags;
} i386_interrupt_frame_t;


ALIGN(IDT_ALIGN)
static i386_descriptor_t idt[IDT_COUNT];


INTERRUPT
static void divide_error_handler(UNUSED i386_interrupt_frame_t* frame)
{
    vga_write(DIVIDE_ERROR_MESSAGE, sizeof(DIVIDE_ERROR_MESSAGE) - 1);
    halt();
}

void setup_idt(void)
{
    idt[0] = I386_INTERRUPT_GATE_DESCRIPTOR(
        divide_error_handler,
        I386_SEGMENT(I386_RING_0, I386_SEGMENT_GDT, 1),
        I386_RING_0
    );

    load_idt(&I386_DESCRIPTOR_TABLE_REGISTER(idt, IDT_COUNT));
}