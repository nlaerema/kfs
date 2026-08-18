SECTIONS
{
    . = 2M;

    .multiboot ALIGN(32) :
    {
        *(.multiboot)
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
        boot_stack_bottom = .;
        *(.boot_stack)
        boot_stack_top = .;
    }

    /DISCARD/ : {
        *(.comment)
    }
}