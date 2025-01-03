OUTPUT_FORMAT(elf32-i386)
ENTRY(start)

SECTIONS
{
    . = 0x100000;                /* Set the starting address for the kernel */

    .text ALIGN(4K) : {
        *(.text)                 /* All .text sections from input files */
    }

    .data ALIGN(4K) : {
        *(.data)                 /* All .data sections from input files */
    }

    .bss ALIGN(4K) : {
        *(.bss)                  /* All .bss sections from input files */
    }
}