#ifndef _LIMITS_H
#define _LIMITS_H

/*
 * Sizes of data types.
 */

#include <wordsize.h>

#define CHAR_BIT	8

#define SCHAR_MIN	(-128)
#define SCHAR_MAX	127

#define UCHAR_MAX	255

#define CHAR_MAX	UCHAR_MAX
#define CHAR_MIN	0

#define SHRT_MAX	32767
#define SHRT_MIN	(-SHRT_MAX - 1)

#define INT_MAX	        2147483647
#define INT_MIN	        (-INT_MAX - 1)

#define UINT_MAX	4294967295U

#define LONG_MAX	2147483647L
#define LONG_MIN	(-LONG_MAX - 1L)

#endif /* _LIMITS_H */
