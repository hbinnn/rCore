#include "exit.h"

extern int user_main();

extern char *user_sbss;
extern char *user_ebss;

void clear_bss()
{
    for (char *p = user_sbss; p < user_ebss; ++p) {
        *p = 0;
    }
}

void user_entry()
{
    clear_bss();
    exit(user_main());
}