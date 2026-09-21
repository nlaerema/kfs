#pragma once


#include "lib/attributes.h"

#include <stdint.h>


PRESERVE_ALL_REGS
uint8_t in8(uint16_t port);

PRESERVE_ALL_REGS
uint16_t in16(uint16_t port);

PRESERVE_ALL_REGS
uint32_t in32(uint16_t port);


PRESERVE_ALL_REGS
void out8(uint16_t port, uint8_t value);

PRESERVE_ALL_REGS
void out16(uint16_t port, uint16_t value);

PRESERVE_ALL_REGS
void out32(uint16_t port, uint32_t value);