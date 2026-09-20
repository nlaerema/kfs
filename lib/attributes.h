#pragma once

#define ALIGN(n)                  __attribute__((aligned(n)))
#define INTERRUPT                 __attribute__((interrupt))
#define NAKED                     __attribute__((naked))
#define NO_CALLER_SAVED_REGISTERS __attribute__((no_caller_saved_registers))
#define NORETURN                  __attribute__((noreturn))
#define PACKED                    __attribute__((packed))
#define REGPARAM(n)               __attribute__((regparm(n)))
#define SECTION(name)             __attribute__((section(name), used))
#define UNUSED                    __attribute__((unused))
#define USED                      __attribute__((used))