#pragma once

#define ALIGN(n)      __attribute__((aligned(n)))
#define NAKED         __attribute__((naked))
#define NORETURN      __attribute__((noreturn))
#define PACKED        __attribute__((packed))
#define SECTION(name) __attribute__((section(name), used))
#define USED          __attribute__((used))