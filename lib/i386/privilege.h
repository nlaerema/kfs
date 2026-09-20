#pragma once


#include <stdint.h>


typedef enum : uint8_t {
    I386_RING_0 = 0,
    I386_RING_1 = 1,
    I386_RING_2 = 2,
    I386_RING_3 = 3,
} i386_privilege_level_t;