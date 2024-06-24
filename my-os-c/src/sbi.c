#include "sbi.h"
#include "types.h"

#define SBI_CONSOLE_PUTCHAR_EID 0x1
#define SBI_CONSOLE_PUTCHAR_FID 0x0

#define SBI_SYSTEM_RESET_EID    0x53525354
#define SBI_SYSTEM_RESET_FID    0x0

int inline sbi_call(uint64 eid, uint64 fid, uint64 arg0, uint64 arg1)
{
    register uint64 a0 asm("a0") = arg0;
    register uint64 a1 asm("a1") = arg1;
    register uint64 a6 asm("a6") = fid;
    register uint64 a7 asm("a7") = eid;

    asm volatile("ecall"
                 : "=r"(a0), "=r"(a1)
                 : "r"(a0), "r"(a1), "r"(a6), "r"(a7)
                 : "memory");

    return a0;
}

void sbi_putchar(char c)
{
    sbi_call(SBI_CONSOLE_PUTCHAR_EID, SBI_CONSOLE_PUTCHAR_FID, c, 0);
}

void sbi_reset(uint64 reset_type, uint64 reset_reason)
{
    sbi_call(SBI_SYSTEM_RESET_EID, SBI_SYSTEM_RESET_FID, reset_type, reset_reason);
}