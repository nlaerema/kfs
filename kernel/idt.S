.intel_syntax


.include "macros.inc"


.text

FUNCTION_START load_idt
    lidt [eax]
    ret
FUNCTION_END load_idt