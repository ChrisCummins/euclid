/**
 * @file stdarg.h
 *
 * Handle variable argument list. The <stdarg.h> contains a set of macros which
 * allows portable functions that accept variable argument lists to be
 * written.
 */

#ifndef _STDARG_H
#define _STDARG_H

#include <macros.h>

/**
 * The variables used to traverse variable argument lists.
 */
typedef char *va_list;

/**
 * This initialises ap for subsequent use by va_arg() and va_end(), and must be
 * called first. The argument 'last' is the name of the last argument before the
 * variable argument list.
 */
#define va_start(ap, last) (ap = (va_list) &last + _INTSIZEOF(last))

/**
 * This produces an expression that has the type and value of the next argument
 * in the call. Each call to va_arg() modifies ap so that the next call returns
 * the next argument.
 */
#define va_arg(ap, type) (*(type *)((ap += _INTSIZEOF(type)) - _INTSIZEOF(type)))

/**
 * Each invocation of va_start() must be matched by a corresponding invocation
 * of va_end() in the same function. After the call va_end(ap), the variable
 * 'ap' is undefined.
 */
#define va_end(ap) (ap = (va_list) 0)

/**
 * Added for completeness.
 */
#define va_copy(destination, source) (destination = source)

#endif /* _STDARG_H */
