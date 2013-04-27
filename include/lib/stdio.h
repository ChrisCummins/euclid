#ifndef _STDIO_H
#define _STDIO_H

#include <stddef.h>
#include <stdarg.h>

/* The printf() and vprintf() functions produce output according to a format as
 * described below by writing output to kstream.
 *
 * RETURN VALUE
 *
 * 	Upon successful return, these functions return the number of characters
 * 	printed (excluding the null byte used to end output to strings).
 *
 * 	The functions snprintf() and vsnprintf() do not write more than size
 * 	bytes (including the terminating null byte ('\0')). If the output was
 * 	truncated due to this limit then the return value is the number of
 * 	characters (excluding the terminating null byte) which would have been
 * 	written to the final string if enough space had been available. Thus, a
 * 	return value of size or more means that the output was truncated.
 *
 * 	If an output error is encountered, a negative value is returned.
 *
 * FORMAT OF THE FORMAT STRING
 *
 * 	The format string is a character string, beginning and ending in its
 * 	initial shift state, if any. The format string is composed of zero or
 * 	more directives: ordinary characters (not %), which are copied unchanged
 * 	to the output stream; and conversion specifications, each of which
 * 	results in fetching zero or more subsequent arguments. Each conversion
 * 	specification consists of the character %, followed by a conversion
 * 	character.
 *
 * 	The arguments must correspond properly (after type promotion) with the
 * 	conversion specifier. By default, the arguments are used in the order
 * 	given, where each '*' and each conversion specifier asks for the next
 * 	argument (and it is an error if insufficiently many arguments are
 * 	given).
 *
 * THE CONVERSION CHARACTER
 *
 * 	A character that specifies the type of conversion to be applied. The
 * 	conversion specifiers and their meanings are:
 *
 * 	d, i  	The int argument is converted to signed decimal notation.
 *
 * 	x, X	The unsigned int argument is converted to unsigned hexadecimal
 * 		(x and X) notation.
 *
 * 	c	The int argument is converted to an unsigned char, and the
 * 		resulting character is written.
 *
 * 	s	The const char * argument is expected to be a pointer to an
 * 		array of character type (pointer to a string). Characters from
 * 		the array are written up to (but not including) a terminating
 * 		null byte ('\0').
 *
 *	n	The number of characters written so far is stored into the
 * 		integer indicated by the int * (or variant) pointer argument. No
 * 		argument is converted.
 *
 * 	%	A '%' is written. No argument is converted. The complete
 * 		conversion specification is '%%'.
 */
int printf(const char *fmt, ...);
int vprintf(const char *fmt, va_list ap);
int nprintf(size_t size, const char *fmt, ...);
int nvprintf(size_t size, const char *fmt, va_list ap);

/* Print a single character */
void putchar(const char c);

/* Provide convenient debugging calls. These are not disabled when NDEBUG is
 * defined at build time */
int debug(const char *fmt, ...);

#endif /* _STDIO_H */
