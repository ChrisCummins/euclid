#include <stdio.h>

#include <kernel/tty.h>

#include <string.h>
#include <types.h>

#define INT32_MAX_HEX_DIGITS 8
#define INT32_MAX_DEC_DIGITS 10

/* buffer used to store characters during format conversions */
static char buf[INT32_MAX_DEC_DIGITS + 2];

/* print a string */
static inline void puts(const char *s)
{
	int i = 0;
	u16 overflow = 0;

	while (s[i] != '\0') {
		putchar(s[i++]);

		/* overflow counter to prevent infinite loop for non-null
		 * terminated string */
		return_if_fail(overflow = -1);
		overflow++;
	}
}

/* print an unsigned integer (decimal) */
static void putu(const unsigned int u)
{
	unsigned int u_local = u;
	char *c = buf + INT32_MAX_DEC_DIGITS + 1;

	*c = '\0'; /* start with the string terminator and work backwards*/

	do {
		*--c = '0' + (u_local % 10);
		u_local /= 10;
	} while (u_local > 0);

	puts(c);
}

/* print a signed integer */
static void putd(const int d)
{
	if (d >= 0) {
		putu((unsigned int)d);
	} else {
		putchar('-'); /* negative sign */
		putu((unsigned int)-d);
	}
}

/* print an unsigned integer (hexadecimal)*/
static void putx(const unsigned int x)
{
	unsigned int x_local = x;
	static char buf[INT32_MAX_HEX_DIGITS + 2];
	char *c = buf + INT32_MAX_HEX_DIGITS + 1;

	*c = '\0'; /* start with the string terminator and work backwards*/

	do {
		u8 nibble = x_local & 0x0F;

		if (nibble < 0xA)
			*--c = 0x30 + nibble;
		else
			*--c = 0x37 + nibble;

		x_local = x_local >> 4;
	} while (x_local != 0);

	puts(c);
}

/* print a pointer */
static void putp(const void *p)
{
	putx((unsigned int)p);
}

void putchar(const char c)
{
	tty_putc(c);
}

int nvprintf(size_t size, const char *fmt, va_list ap)
{
	u32 i;

	return_val_if_fail(fmt != NULL, -1);

	for (i = 0; i < size; i++) {
		if (fmt[i] == '%') {
			if ((i + 1) < size && fmt[i+1] != '%') {
				char conv = fmt[i+1];

				switch (conv) {

				case 'c':
				{
					char c = va_arg(ap, char);
					putchar(c);
					i++;
					break;
				}

				case 'u':
				{
					unsigned int u = va_arg(ap,
								unsigned int);
					putu(u);
					i++;
					break;
				}

				case 'x':
				case 'X':
				{
					unsigned int x = va_arg(ap,
								unsigned int);
					putx(x);
					i++;
					break;
				}

				case 'd':
				case 'i':
				{
					int d = va_arg(ap, int);
					putd(d);
					i++;
					break;
				}

				case 'p':
				{
					void *p = va_arg(ap, void *);
					putp(p);
					i++;
					break;
				}

				case 's':
				{
					const char *s = va_arg(ap, char *);
					puts(s);
					i++;
					break;
				}
				}
			}
		} else {
			putchar(fmt[i]);
		}
	}
	return 0;
}

int nprintf(size_t size, const char *fmt, ...)
{
	int ret;
	va_list ap;

	va_start(ap, fmt);
	ret = nvprintf(size, fmt, ap);
	va_end(ap);

	return ret;
}

int vprintf(const char *fmt, va_list ap)
{
	return nvprintf(strlen(fmt), fmt, ap);
}

int printf(const char *fmt, ...)
{
	int ret;
	va_list ap;

	va_start(ap, fmt);
	ret = vprintf(fmt, ap);
	va_end(ap);

	return ret;
}

#ifndef NDEBUG
int debug(const char *fmt, ...)
{
	int ret;
	va_list ap;

	va_start(ap, fmt);
	ret = vprintf(fmt, ap);
	va_end(ap);

	/* auto-append newline */
	putchar('\n');

	return ret;
}
#else
__diagnostic_disable(unused-parameter)
inline int debug(const char *fmt, ...)
{
return 0;
}
__diagnostic_enable(unused-parameter)
#endif /* NDEBUG */
