.intel_syntax


.include "lib/macros.inc"


.text

FUNCTION_START load_idt
    lidt [eax]
    ret
FUNCTION_END load_idt