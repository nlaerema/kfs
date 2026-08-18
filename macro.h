#pragma once

#define SECTION(name) __attribute__((section(name), used))
#define USED __attribute__((used))
#define ALIGN(n) __attribute__((aligned(n)))
#define NORETURN __attribute__((noreturn))
#define NAKED __attribute__((naked))
#define PACKED __attribute__((packed))