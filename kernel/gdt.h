#pragma once


#include "attributes.h"
#include "i386/descriptor_table.h"


REGPARAM(1)
void load_gdt(const i386_descriptor_table_register_t* gdt_register);

REGPARAM(2)
void load_gdt_segments(i386_segment_t code_segment, i386_segment_t data_segment);

void setup_gdt(void);