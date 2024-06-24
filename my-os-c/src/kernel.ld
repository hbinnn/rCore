OUTPUT_ARCH(riscv)
ENTRY(_entry)
BASE_ADDRESS = 0x80200000;

SECTIONS
{
    . = BASE_ADDRESS;
    skernel = .;
    
    stext = .;
    .text : {
        *(.text.entry)
        *(.text .text.*)
    }
    . = ALIGN(0x1000);
    etext = .;

    srodata = .;
    .rodata : {
        *(.rodata .rodata.*)
    }
    . = ALIGN(0x1000);
    erodata = .;

    sdata = .;
    .data : {
        *(.data .data.*)
    }
    . = ALIGN(0x1000);
    edata = .;

    .bss : {
        *(.bss.stack)
        sbss = .;
        *(.bss .bss.*)
    }
    . = ALIGN(0x1000);
    ebss = .;

    ekernel = .;

    /DISCARD/ : {
        *(.eh_frame)
    }
}