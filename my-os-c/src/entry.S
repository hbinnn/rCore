.section .text.entry
.globl _entry

_entry:
    la sp, kernel_stack_top
    call kernel_main

.section .bss.stack
.globl kernel_stack_lower_bound

kernel_stack_lower_bound:
    .space 0x1000 * 64

.globl kernel_stack_top

kernel_stack_top: