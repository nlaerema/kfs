#pragma once

#define ALIGN(n)      __attribute__((aligned(n)))
#define NAKED         __attribute__((naked))
#define NORETURN      __attribute__((noreturn))
#define PACKED        __attribute__((packed))
#define REGPARAM(n)   __attribute__((regparm(n)))
#define SECTION(name) __attribute__((section(name), used))
#define USED          __attribute__((used))