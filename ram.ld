ENTRY(isr_reset)

MEMORY
{
    TCM (rx)         :ORIGIN = 0x20020000, LENGTH = 128K
    RAM (xrw)        :ORIGIN = 0x20000000, LENGTH = 128K
    STACK (rw)       :ORIGIN = 0x20040000, LENGTH = 4K
    STACK_CORE1 (rw) :ORIGIN = 0x20041000, LENGTH = 4K
}

_stack_top = ORIGIN(STACK) + LENGTH(STACK);
_stack_top_core1 = ORIGIN(STACK_CORE1) + LENGTH(STACK_CORE1);

SECTIONS
{
    .isr_vector :
    {
        . = ALIGN(4);
        _vector_load = LOADADDR(.isr_vector);
        KEEP(*(.isr_vector))
        . = ALIGN(4);
    } >TCM

    .text :
    {
        . = ALIGN(4);
        *(.text)           /* .text sections (code) */
        *(.text*)          /* .text* sections (code) */
        . = ALIGN(4);
    } >TCM

    .rodata :
    {
        . = ALIGN(4);
        *(.rodata)
        *(.rodata*)
        . = ALIGN(4);
    } >TCM

    .data :
    {
        . = ALIGN(4);
        _data_load = LOADADDR(.data);
        _data_run = .;
        *(.data)
        *(.data.*)
        . = ALIGN(4);
        _data_run_end = .;
    } >RAM AT>TCM

    .bss (NOLOAD) :
    {
        . = ALIGN(4);
        _bss_run = .;
        *(.bss)
        *(.bss.*)
        . = ALIGN(4);
        _bss_run_end = .;
    } >RAM
}
