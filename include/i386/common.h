#pragma once


#include <stdint.h>

#include "attributes.h"


#define I386_SEGMENT(_privilege_level, _table_indicator, _index) \
    ((i386_segment_t) { \
        .privilege_level = (_privilege_level), \
        .table_indicator = (_table_indicator), \
        .index           = (_index), \
    })


typedef enum : uint8_t {
    I386_RING_0 = 0,
    I386_RING_1 = 1,
    I386_RING_2 = 2,
    I386_RING_3 = 3,
} i386_privilege_level_t;


typedef enum : uint8_t {
    I386_SEGMENT_GDT = 0,
    I386_SEGMENT_LDT = 1,
} i386_segment_table_t;

typedef union PACKED {
    uint16_t raw;

    struct PACKED {
        i386_privilege_level_t privilege_level : 2;
        i386_segment_table_t table_indicator   : 1;
        uint16_t index                         : 13;
    };
} i386_segment_t;

static_assert(sizeof(i386_segment_t) == 2, "i386_segment_t must be 2 bytes");