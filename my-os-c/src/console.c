#include "console.h"
#include "sbi.h"

void console_putchar(char c)
{
    sbi_putchar(c);
}