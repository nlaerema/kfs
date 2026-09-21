#pragma once

#define ALIGN(n)          __attribute__((aligned(n)))
#define INTERRUPT         __attribute__((interrupt))
#define NAKED             __attribute__((naked))
#define PRESERVE_ALL_REGS __attribute__((no_caller_saved_registers))
#define NORETURN          __attribute__((noreturn))
#define PACKED            __attribute__((packed))
#define SECTION(name)     __attribute__((section(name), used))
#define UNUSED            __attribute__((unused))
#define USED              __attribute__((used))