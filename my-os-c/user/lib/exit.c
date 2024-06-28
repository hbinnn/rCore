#include "exit.h"
#include "sys_call.h"

int exit(int status)
{
    return sys_exit(status);
}