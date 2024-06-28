#include <stddef.h>
#include "../lib/print.h"

int user_main()
{
    print("Kernel should kill this application!");
    char *invalid_ptr = NULL;
    *invalid_ptr = 's';
    return 0;
}