#include "write.h"
#include "sys_call.h"

int write(int fd, void *buf, int len)
{
    return sys_write(fd, buf, len);
}