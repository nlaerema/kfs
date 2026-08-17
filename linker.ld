ENTRY(_start)

SECTIONS
{
    . = 1M;

    .multiboot :
    {
        *(.multiboot)
        *(.multiboot.*)
    }

    .text :
    {
        *(.text)
        *(.text.*)
    }

    .rodata :
    {
        *(.rodata)
        *(.rodata.*)
    }

    .data :
    {
        *(.data)
        *(.data.*)
    }

    .bss :
    {
        *(.bss)
        *(.bss.*)
        *(COMMON)
    }

    .boot_stack ALIGN(16) :
    {
        *(.boot_stack)
    }
}