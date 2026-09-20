.intel_syntax


.include "lib/macros.inc"


.text

FUNCTION_START _start
    mov esp, offset boot_stack_top
    mov edx, ebx
    jmp kernel_main
FUNCTION_END _start