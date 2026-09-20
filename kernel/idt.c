#include "idt.h"

#include "drivers/vga.h"

#include "lib/attributes.h"
#include "lib/i386/descriptor_table.h"


#define IDT_COUNT 256
#define IDT_ALIGN 8


REGPARAM(1)
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
    vga_write("DIVISION BY ZERO", 1);
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