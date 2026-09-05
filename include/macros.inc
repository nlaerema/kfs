.macro FUNCTION_START name
    .global \name
    .type \name, @function
\name:
.endm

.macro FUNCTION_END name
    .size \name, .-\name
.endm

.macro STACK_FRAME_CREATE size
    push ebp
    mov ebp, esp
    sub esp, \size
.endm

.macro STACK_FRAME_DESTROY
    leave
.endm