SECTIONS
{
    . = 2M;

    .multiboot :
    {
        *(.multiboot2)
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

    .boot_stack :
    {
        boot_stack_bottom = .;
        *(.boot_stack)
        boot_stack_top = .;
    }

    /DISCARD/ : {
        *(.comment)
    }
}