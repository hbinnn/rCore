#include <stdarg.h>
#include <stddef.h>
#include "string.h"
#include "../../src/types.h"
#include "print.h"
#include "write.h"

#define STDIN 1

static char digits[] = "0123456789abcdef";

static void printint(int xx, int base, int sign)
{
	char buf[16];
	int i;
	uint x;

	if (sign && (sign = xx < 0))
		x = -xx;
	else
		x = xx;

	i = 0;
	do {
		buf[i++] = digits[x % base];
	} while ((x /= base) != 0);

	if (sign)
		buf[i++] = '-';

	while (--i >= 0)
		write(STDIN, &buf[i], 1);
}

static void printptr(uint64 x)
{
	int i;
	char tmp = '0';
	write(STDIN, &tmp, 1);
	tmp = 'x';
	write(STDIN, &tmp, 1);
	for (i = 0; i < (sizeof(uint64) * 2); i++, x <<= 4)
		write(STDIN, &digits[x >> (sizeof(uint64) * 8 - 4)], 1);
}

void print(const char *fmt, ...)
{
    va_list ap;
	int i, c;
	char *s;
	char tmp;

	if (fmt == NULL) {
        return;
    }

	va_start(ap, fmt);
	for (i = 0; (c = fmt[i] & 0xff) != 0; i++) {
		if (c != '%') {
			write(STDIN, &c, 1);
			continue;
		}
		c = fmt[++i] & 0xff;
		if (c == 0)
			break;
		switch (c) {
		case 'd':
			printint(va_arg(ap, int), 10, 1);
			break;
		case 'x':
			printint(va_arg(ap, int), 16, 1);
			break;
		case 'p':
			printptr(va_arg(ap, uint64));
			break;
		case 's':
			if ((s = va_arg(ap, char *)) == 0)
				s = "(null)";
			write(STDIN, s, strlen(s));
			break;
		case '%':
			write(STDIN, &c, 1);
			break;
		default:
			// Print unknown % sequence to draw attention.
			tmp = '%';
			write(STDIN, &tmp, 1);
			write(STDIN, &c, 1);
			break;
		}
	}
}