ENTRY(_start)

SECTIONS {
    . = 0x0; /* Start address for your program */
    .text : {
        *(.text)
    }
    .data : {
        *(.data)
    }
    .bss : {
        *(.bss)
    }
}
