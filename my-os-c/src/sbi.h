#ifndef SBI_H
#define SBI_H

#include "types.h"

typedef enum {
    SBI_SHUTDOWN,
    SBI_COLD_REBOOT,
    SBI_WARM_REBOOT,
    SBI_INVALID_RESET_TYPE
} SBI_SYSTEM_RESET_TYPE;

typedef enum {
    SBI_NO_REASON,
    SBI_SYSTEM_FAILURE,
    SBI_INVALID_RESET_REASON
} SBI_SYSTEM_RESET_REASON;

void sbi_putchar(char c);

void sbi_reset(uint64 reset_type, uint64 reset_reason);

#endif