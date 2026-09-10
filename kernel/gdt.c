#include "gdt.h"
#include "i386/descriptor_table.h"


#define GDT_COUNT 3
#define GDT_ALIGN 8


ALIGN(GDT_ALIGN)
static i386_descriptor_t gdt[GDT_COUNT] = {
    I386_NULL_DESCRIPTOR(),
    I386_CODE_DESCRIPTOR(0, 0xFFFFF, I386_RING_0, 1, 1, 0, 1),
    I386_DATA_DESCRIPTOR(0, 0xFFFFF, I386_RING_0, 1, 1, 0, 1),
};


void setup_gdt(void)
{
    load_gdt(&I386_DESCRIPTOR_TABLE_REGISTER(gdt, GDT_COUNT));
    load_gdt_segments(
        I386_SEGMENT(I386_RING_0, I386_SEGMENT_GDT, 1),
        I386_SEGMENT(I386_RING_0, I386_SEGMENT_GDT, 2)
    );
}