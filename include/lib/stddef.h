/*
 * Standard type definitions.
 */

#ifndef _STDDEF_H
#define _STDDEF_H

/* Null pointer constant. */
#define NULL ((void*) 0)

/* Integer constant expression of type size_t, the value of which is the offset
 * in bytes to the structure member (member-designator), from the beginning of
 * its structure (type).
 */
#define offsetof(type, member) ((size_t)(&((type *)0)->member))

/* Unsigned integer type of the result of the sizeof operator. */
typedef unsigned int size_t;

/* Integer type whose range of values can represent distinct wide-character
 * codes for all members of the largest character set specified among the
 * locales supported by the compilation environment: the null character has the
 * code value 0 and each member of the portable character set has a code value
 * equal to its value when used as the lone character in an integer character
 * constant.
 */
typedef int wchar_t;

/* Signed integer type of the result of subtracting two pointers. */
typedef long int ptrdiff_t;

#endif /* _STDDEF_H */
