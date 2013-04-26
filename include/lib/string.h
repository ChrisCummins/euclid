/*
 * String operations
 */

#ifndef _STRING_H
#define _STRING_H

#include <types.h>

#define is_digit(c) ((c) >= '0' && (c) <= '9')

/* Calculates the length of the string s, excluding the terminating null byte
 * ('\0'). It returns the number of bytes in the string. */
size_t strlen(const char *s);


/* Copies the string pointed to by src, including the
 * terminating null byte ('\0'), to the buffer pointed to by dest. The strings
 * may not overlap, and the destination string dest must be large enough to
 * receive the copy.
 */
char *strcpy(char *dest, const char *src);

/* Similar to strcpy(), except that at most n bytes of src are copied. Warning:
 * If there is no null byte among the first n bytes of src, the string placed in
 * dest will not be null-terminated. If the length of src is less than n,
 * strncpy() writes additional null bytes to dest to ensure that a total of n
 * bytes are written.
 */
char *strncpy(char *dest, const char *src, size_t n);


/* Compares the two strings s1 and s2. It returns an integer less than, equal
 * to, or greater than zero if s1 is found, respectively, to be less than, to
 * match, or be greater than s2.
 */
int strcmp(const char *s1, const char *s2);

/* Similar to strcmp(), except it only compares the first (at most) n bytes of
 * s1 and s2.
 */
int strncmp(const char *s1, const char *s2, size_t n);


/* Copies n bytes from memory area src to memory area dest. The memory areas
 * must not overlap. Use memmove() if the memory areas do overlap.
 */
void *memcpy(void *dest, const void *src, size_t n);

/* Fills the first n bytes of the memory area pointed to by s with the constant
 * byte c.
 */
void *memset(void *s, char c, size_t n);

#endif /* _STRING_H */
