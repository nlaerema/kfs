.intel_syntax

.text

.global _start
.type _start, @function
_start:
    lea esp, [boot_stack_top]
    jmp kernel_main
