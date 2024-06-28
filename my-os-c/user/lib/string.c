#include "string.h"
#include <stddef.h>

int strlen(void *s)
{
    int ret = 0;
    while (s != NULL) {
        ret++;
        s++;
    }
    return ret;
}