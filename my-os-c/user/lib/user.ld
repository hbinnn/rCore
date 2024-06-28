OUTPUT_ARCH(riscv)
ENTRY(_user_entry)

BASE_ADDRESS = 0x80400000;

SECTIONS
{
    . = BASE_ADDRESS;
    .text : {
        *(.text.entry)
        *(.text .text.*)
    }

    .rodata : {
        *(.rodata .rodata.*)
        *(.srodata .srodata.*)
    }

    .data : {
        *(.data .data.*)
        *(.sdata .sdata.*)
    }

    .bss : {
        user_sbss = .;
        *(.bss .bss.*)
        *(.sbss .sbss.*)
        user_ebss = .;
    }

    /DISCARD/ : {
        *(.eh_frame)
        *(.debug*)
    }
}