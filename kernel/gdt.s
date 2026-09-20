.intel_syntax


.include "lib/macros.inc"


.text

FUNCTION_START load_gdt
    lgdt [eax]
    ret
FUNCTION_END load_gdt


FUNCTION_START load_gdt_segments
    STACK_FRAME_CREATE 8

    mov dword ptr [esp], offset load_data_segments
    mov word ptr [esp + 4], ax

    ljmp [esp]

load_data_segments:
    mov ds, dx
    mov es, dx
    mov fs, dx
    mov gs, dx
    mov ss, dx

    STACK_FRAME_DESTROY
    ret
FUNCTION_END load_gdt_segments