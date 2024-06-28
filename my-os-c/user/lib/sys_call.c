#include "sys_call.h"

typedef enum {
    SYSCALL_WRITE = 64,
    SYSCALL_EXIT = 93
} SYSCALL_ID;

int sys_call(SYSCALL_ID id, uint64 arg0, uint64 arg1, uint64 arg2,
    uint64 arg3, uint64 arg4, uint64 arg5)
{
    register uint64 a0 asm("a0") = arg0;
    register uint64 a1 asm("a1") = arg1;
    register uint64 a2 asm("a2") = arg2;
    register uint64 a3 asm("a3") = arg3;
    register uint64 a4 asm("a4") = arg4;
    register uint64 a5 asm("a5") = arg5;
    register uint64 a7 asm("a7") = id;

    asm volatile("ecall"
                 : "=r"(a0)
                 : "r"(a0), "r"(a1), "r"(a2), "r"(a3), "r"(a4), "r"(a5), "r"(a7)
                 : "memory");

    return a0;
}

int sys_write(int fd, void *buf, int len)
{
    return sys_call(SYSCALL_WRITE, fd, (uint64)buf, len, 0, 0, 0);
}

int sys_exit(int state)
{
    return sys_call(SYSCALL_EXIT, state, 0, 0, 0, 0, 0);
}