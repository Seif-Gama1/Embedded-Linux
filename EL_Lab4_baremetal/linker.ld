ENTRY(_start)

SECTIONS
{
    /* da el address el h3ml feh load lel app */
    . = 0x80000; /* only limitation is, don't put it in reserved area */
    __start = .;
    .text :
    {
        KEEP(*(.text.boot))
       *(.text)
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
    /* the "." address keeps incrementing, so for example "." equals 0x60101000 */
    __bss_start = .;
    .bss :
    {
        *        *(.bss)
        *(.bss.*)
        *(COMMON)
    }
    __bss_end = .;
    __end = .; /* can be used to keep find the size of the app */
    __size_of_map = __end - __start;
    __bss_size = __bss_end - __bss_start;

    . = ALIGN(16);
    _stack_top = . + 0x4000;   /* 16 KB stack */
}