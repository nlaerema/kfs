.intel_syntax


.include "lib/macros.inc"


.text

FUNCTION_START in8
    mov dx, ax
    in al, dx
    ret
FUNCTION_END in8

FUNCTION_START in16
    mov dx, ax
    in ax, dx
    ret
FUNCTION_END in16

FUNCTION_START in32
    mov dx, ax
    in eax, dx
    ret
FUNCTION_END in32


FUNCTION_START out8
    xchg eax, edx
    out dx, al
    ret
FUNCTION_END out8

FUNCTION_START out16
    xchg eax, edx
    out dx, ax 
    ret
FUNCTION_END out16

FUNCTION_START out32
    xchg eax, edx
    out dx, eax
    ret
FUNCTION_END out32