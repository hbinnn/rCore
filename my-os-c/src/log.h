#ifndef LOG_H
#define LOG_H

#include "print.h"

#define USE_LOG_ERROR
#define USE_LOG_WARN
#define USE_LOG_INFO
#define USE_LOG_DEBUG
#define USE_LOG_TRACE

enum LOG_COLOR {
	RED = 31,
	GREEN = 32,
	BLUE = 34,
	GRAY = 90,
	YELLOW = 93,
};

static inline int threadid()
{
    return 0;
}

#define errorf(fmt, ...)                                               \
	do {                                                               \
		int tid = threadid();                                          \
		print("\x1b[%dm[%s %d]" fmt "\x1b[0m\n", RED, "ERROR", tid,    \
		       ##__VA_ARGS__);                                         \
	} while (0)

#define warnf(fmt, ...)                                                \
	do {                                                               \
		int tid = threadid();                                          \
		print("\x1b[%dm[%s %d]" fmt "\x1b[0m\n", YELLOW, "WARN", tid,  \
		       ##__VA_ARGS__);                                         \
	} while (0)

#define infof(fmt, ...)                                                \
	do {                                                               \
		int tid = threadid();                                          \
		print("\x1b[%dm[%s %d]" fmt "\x1b[0m\n", BLUE, "INFO", tid,    \
		       ##__VA_ARGS__);                                         \
	} while (0)

#define debugf(fmt, ...)                                               \
	do {                                                               \
		int tid = threadid();                                          \
		print("\x1b[%dm[%s %d]" fmt "\x1b[0m\n", GREEN, "DEBUG", tid,  \
		       ##__VA_ARGS__);                                         \
	} while (0)

#define tracef(fmt, ...)                                               \
	do {                                                               \
		int tid = threadid();                                          \
		print("\x1b[%dm[%s %d]" fmt "\x1b[0m\n", GRAY, "TRACE", tid,   \
		       ##__VA_ARGS__);                                         \
	} while (0)

#define panic(fmt, ...)                                                \
	do {                                                               \
		int tid = threadid();                                          \
		print("\x1b[%dm[%s %d] %s:%d: " fmt "\x1b[0m\n", RED,          \
		       "PANIC", tid, __FILE__, __LINE__, ##__VA_ARGS__);       \
		shutdown();                                                    \
	} while (0)

#endif