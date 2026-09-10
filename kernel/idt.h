#pragma once


#include <stdint.h>

#include "attributes.h"
#include "i386/descriptor_table.h"


typedef struct {
    uint32_t eip;
    uint32_t cs;
    uint32_t eflags;
} i386_interrupt_frame_t;


REGPARAM(1)
void load_idt(const i386_descriptor_table_register_t* idt_register);

void setup_idt(void);