#pragma once


#include <stdint.h>

#include "attributes.h"
#include "i386/common.h"


#define I386_NULL_DESCRIPTOR() \
    ((i386_descriptor_t) { \
        .raw = 0 \
    })

#define I386_CODE_DESCRIPTOR(_base, _limit, _privilege_level, _granularity, _readable, _conforming, _default_size) \
    ((i386_descriptor_t) { \
        .code = { \
            .limit_low      = (uint16_t)(_limit), \
            .base_low       = (uint16_t)(_base), \
            .base_middle    = (uint8_t)((_base) >> 16), \
            .accessed       = 0, \
            .readable       = (_readable), \
            .conforming     = (_conforming), \
            .executable     = 1, \
            .system         = 1, \
            .privilege_level= (_privilege_level), \
            .present        = 1, \
            .limit_high     = (uint8_t)((_limit) >> 16), \
            .available      = 0, \
            .reserved       = 0, \
            .default_size   = (_default_size), \
            .granularity    = (_granularity), \
            .base_high      = (uint8_t)((_base) >> 24), \
        } \
    })

#define I386_DATA_DESCRIPTOR(_base, _limit, _privilege_level, _granularity, _writable, _expand_down, _default_size) \
    ((i386_descriptor_t) { \
        .data = { \
            .limit_low      = (uint16_t)(_limit), \
            .base_low       = (uint16_t)(_base), \
            .base_middle    = (uint8_t)((_base) >> 16), \
            .accessed       = 0, \
            .writable       = (_writable), \
            .expand_down    = (_expand_down), \
            .executable     = 0, \
            .system         = 1, \
            .privilege_level= (_privilege_level), \
            .present        = 1, \
            .limit_high     = (uint8_t)((_limit) >> 16), \
            .available      = 0, \
            .reserved       = 0, \
            .default_size   = (_default_size), \
            .granularity    = (_granularity), \
            .base_high      = (uint8_t)((_base) >> 24), \
        } \
    })

#define I386_LDT_DESCRIPTOR(_base, _limit, _privilege_level) \
    ((i386_descriptor_t) { \
        .ldt = { \
            .limit_low      = (uint16_t)(_limit), \
            .base_low       = (uint16_t)(_base), \
            .base_middle    = (uint8_t)((_base) >> 16), \
            .type           = I386_LDT_DESCRIPTOR, \
            .system         = 0, \
            .privilege_level= (_privilege_level), \
            .present        = 1, \
            .limit_high     = (uint8_t)((_limit) >> 16), \
            .available      = 0, \
            .reserved       = 0, \
            .base_high      = (uint8_t)((_base) >> 24), \
        } \
    })

#define I386_TSS_DESCRIPTOR(_base, _limit, _privilege_level) \
    ((i386_descriptor_t) { \
        .tss = { \
            .limit_low      = (uint16_t)(_limit), \
            .base_low       = (uint16_t)(_base), \
            .base_middle    = (uint8_t)((_base) >> 16), \
            .type           = I386_TSS_AVAILABLE_DESCRIPTOR, \
            .system         = 0, \
            .privilege_level= (_privilege_level), \
            .present        = 1, \
            .limit_high     = (uint8_t)((_limit) >> 16), \
            .available      = 0, \
            .reserved       = 0, \
            .base_high      = (uint8_t)((_base) >> 24), \
        } \
    })

#define I386_CALL_GATE_DESCRIPTOR(_offset, _selector, _privilege_level, _param_count) \
    ((i386_descriptor_t) { \
        .call_gate = { \
            .offset_low     = (uint16_t)(_offset), \
            .selector       = (i386_segment_t)(_selector), \
            .param_count    = (_param_count), \
            .reserved       = 0, \
            .type           = I386_CALL_GATE_DESCRIPTOR, \
            .system         = 0, \
            .privilege_level= (_privilege_level), \
            .present        = 1, \
            .offset_high    = (uint16_t)((_offset) >> 16), \
        } \
    })

#define I386_TASK_GATE_DESCRIPTOR(_tss_selector, _privilege_level) \
    ((i386_descriptor_t) { \
        .task_gate = { \
            .reserved0      = 0, \
            .tss_selector   = (i386_segment_t)(_tss_selector), \
            .reserved1      = 0, \
            .type           = I386_TASK_GATE_DESCRIPTOR, \
            .system         = 0, \
            .privilege_level= (_privilege_level), \
            .present        = 1, \
            .reserved2      = 0, \
        } \
    })

#define I386_INTERRUPT_GATE_DESCRIPTOR(_handler, _selector, _privilege_level) \
    ((i386_descriptor_t) { \
        .interrupt_gate = { \
            .offset_low     = (uint16_t)((uintptr_t)(_handler)), \
            .selector       = (i386_segment_t)(_selector), \
            .reserved       = 0, \
            .type           = I386_INTERRUPT_GATE_DESCRIPTOR, \
            .system         = 0, \
            .privilege_level= (_privilege_level), \
            .present        = 1, \
            .offset_high    = (uint16_t)((uintptr_t)(_handler) >> 16), \
        } \
    })

#define I386_TRAP_GATE_DESCRIPTOR(_handler, _selector, _privilege_level) \
    ((i386_descriptor_t) { \
        .trap_gate = { \
            .offset_low     = (uint16_t)((uintptr_t)(_handler)), \
            .selector       = (i386_segment_t)(_selector), \
            .reserved       = 0, \
            .type           = I386_TRAP_GATE_DESCRIPTOR, \
            .system         = 0, \
            .privilege_level= (_privilege_level), \
            .present        = 1, \
            .offset_high    = (uint16_t)((uintptr_t)(_handler) >> 16), \
        } \
    })

#define I386_DESCRIPTOR_TABLE_REGISTER(_descriptor, _length) \
    ((i386_descriptor_table_register_t) { \
        .limit = (sizeof(i386_descriptor_t) * (_length)) - 1, \
        .base  = (_descriptor), \
    })


typedef enum : uint8_t {
    I386_LDT_DESCRIPTOR            = 2,
    I386_TASK_GATE_DESCRIPTOR      = 5,
    I386_TSS_AVAILABLE_DESCRIPTOR  = 9,
    I386_TSS_BUSY_DESCRIPTOR       = 11,
    I386_CALL_GATE_DESCRIPTOR      = 12,
    I386_INTERRUPT_GATE_DESCRIPTOR = 14,
    I386_TRAP_GATE_DESCRIPTOR      = 15,
} i386_system_descriptor_type_t;


typedef struct PACKED {
    uint16_t               limit_low;
    uint16_t               base_low;
    uint8_t                base_middle;
    bool                   accessed        : 1;
    bool                   readable        : 1;
    bool                   conforming      : 1;
    bool                   executable      : 1;  // = 1
    bool                   system          : 1;  // = 1
    i386_privilege_level_t privilege_level : 2;
    bool                   present         : 1;
    uint8_t                limit_high      : 4;
    bool                   available       : 1;
    bool                   reserved        : 1;
    bool                   default_size    : 1;
    bool                   granularity     : 1;
    uint8_t                base_high;
} i386_code_descriptor_t;

static_assert(sizeof(i386_code_descriptor_t) == 8, "i386_code_descriptor_t must be 8 bytes");


typedef struct PACKED {
    uint16_t               limit_low;
    uint16_t               base_low;
    uint8_t                base_middle;
    bool                   accessed        : 1;
    bool                   writable        : 1;
    bool                   expand_down     : 1;
    bool                   executable      : 1;  // = 0
    bool                   system          : 1;  // = 1
    i386_privilege_level_t privilege_level : 2;
    bool                   present         : 1;
    uint8_t                limit_high      : 4;
    bool                   available       : 1;
    bool                   reserved        : 1;
    bool                   default_size    : 1;
    bool                   granularity     : 1;
    uint8_t                base_high;
} i386_data_descriptor_t;

static_assert(sizeof(i386_data_descriptor_t) == 8, "i386_data_descriptor_t must be 8 bytes");


typedef struct PACKED {
    uint16_t                      limit_low;
    uint16_t                      base_low;
    uint8_t                       base_middle;
    i386_system_descriptor_type_t type            : 4;  // = I386_LDT_DESCRIPTOR
    bool                          system          : 1;  // = 0
    i386_privilege_level_t        privilege_level : 2;
    bool                          present         : 1;
    uint8_t                       limit_high      : 4;
    bool                          available       : 1;
    uint8_t                       reserved        : 3;  // = 0
    uint8_t                       base_high;
} i386_ldt_descriptor_t;

static_assert(sizeof(i386_ldt_descriptor_t) == 8, "i386_ldt_descriptor_t must be 8 bytes");


typedef struct PACKED {
    uint16_t                      limit_low;
    uint16_t                      base_low;
    uint8_t                       base_middle;
    i386_system_descriptor_type_t type            : 4;  // = I386_TSS_AVAILABLE_DESCRIPTOR or I386_TSS_BUSY_DESCRIPTOR
    bool                          system          : 1;  // = 0
    i386_privilege_level_t        privilege_level : 2;
    bool                          present         : 1;
    uint8_t                       limit_high      : 4;
    bool                          available       : 1;
    uint8_t                       reserved        : 3;  // = 0
    uint8_t                       base_high;
} i386_tss_descriptor_t;

static_assert(sizeof(i386_tss_descriptor_t) == 8, "i386_tss_descriptor_t must be 8 bytes");


typedef struct PACKED {
    uint16_t                      offset_low;
    i386_segment_t                selector;
    uint8_t                       param_count     : 5;
    uint8_t                       reserved        : 3;  // = 0
    i386_system_descriptor_type_t type            : 4;  // = I386_CALL_GATE_DESCRIPTOR
    bool                          system          : 1;  // = 0
    i386_privilege_level_t        privilege_level : 2;
    bool                          present         : 1;
    uint16_t                      offset_high;
} i386_call_gate_descriptor_t;

static_assert(sizeof(i386_call_gate_descriptor_t) == 8, "i386_call_gate_descriptor_t must be 8 bytes");


typedef struct PACKED {
    uint16_t                      reserved0;
    i386_segment_t                tss_selector;
    uint8_t                       reserved1;
    i386_system_descriptor_type_t type            : 4;  // = I386_TASK_GATE_DESCRIPTOR
    bool                          system          : 1;  // = 0
    i386_privilege_level_t        privilege_level : 2;
    bool                          present         : 1;
    uint16_t                      reserved2;
} i386_task_gate_descriptor_t;

static_assert(sizeof(i386_task_gate_descriptor_t) == 8, "i386_task_gate_descriptor_t must be 8 bytes");


typedef struct PACKED {
    uint16_t                      offset_low;
    i386_segment_t                selector;
    uint8_t                       reserved        : 8;  // = 0
    i386_system_descriptor_type_t type            : 4;  // = I386_INTERRUPT_GATE_DESCRIPTOR
    bool                          system          : 1;  // = 0
    i386_privilege_level_t        privilege_level : 2;
    bool                          present         : 1;
    uint16_t                      offset_high;
} i386_interrupt_gate_descriptor_t;

static_assert(sizeof(i386_interrupt_gate_descriptor_t) == 8, "i386_interrupt_gate_descriptor_t must be 8 bytes");


typedef struct PACKED {
    uint16_t                      offset_low;
    i386_segment_t                selector;
    uint8_t                       reserved        : 8;  // = 0
    i386_system_descriptor_type_t type            : 4;  // = I386_TRAP_GATE_DESCRIPTOR
    bool                          system          : 1;  // = 0
    i386_privilege_level_t        privilege_level : 2;
    bool                          present         : 1;
    uint16_t                      offset_high;
} i386_trap_gate_descriptor_t;

static_assert(sizeof(i386_trap_gate_descriptor_t) == 8, "i386_trap_gate_descriptor_t must be 8 bytes");


typedef union PACKED {
    uint64_t                         raw;
    i386_code_descriptor_t           code;
    i386_data_descriptor_t           data;
    i386_ldt_descriptor_t            ldt;
    i386_tss_descriptor_t            tss;
    i386_call_gate_descriptor_t      call_gate;
    i386_task_gate_descriptor_t      task_gate;
    i386_interrupt_gate_descriptor_t interrupt_gate;
    i386_trap_gate_descriptor_t      trap_gate;
} i386_descriptor_t;

static_assert(sizeof(i386_descriptor_t) == 8, "i386_descriptor_t must be 8 bytes");


typedef struct PACKED {
    uint16_t limit;
    i386_descriptor_t* base;
} i386_descriptor_table_register_t;

static_assert(sizeof(i386_descriptor_table_register_t) == 6, "i386_descriptor_table_register_t must be 6 bytes");
static_assert(sizeof(i386_descriptor_t*) == 4, "i386_descriptor_t* must be 4 bytes");