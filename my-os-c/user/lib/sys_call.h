#ifndef SYS_CALL_H
#define SYS_CALL_H

#include "../../src/types.h"

int sys_write(int fd, void *buf, int len);

int sys_exit(int state);

#endif