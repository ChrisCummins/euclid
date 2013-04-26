#include <string.h>

#include <keywords.h>

size_t strlen(const char *string)
{
	size_t length = 0;

	if (unlikely(!string)) {
		return (size_t)-1;
	}

	while (*(string + length) != '\0') {
		length++;
	}

	return length;
}

char *strcpy(char *dest, const char *src)
{
	do {
		*dest++ = *src++;
	} while (*src != '\0');

	return dest;
}

char *strncpy(char *dest, const char *src, size_t n)
{
	size_t i;

	for (i = 0; i < n && src[i] != '\0'; i++)
		dest[i] = src[i];

	for ( ; i < n; i++)
		dest[i] = '\0';

	return dest;
}

int strcmp(const char *s1, const char *s2)
{
	int i = 0;

	while (s1[i] != '\0' && s2[i] != '\0') {
		if (s1[i] != s2[i]) {
			return ((s1[i] < s2[2]) ? -1 : 1);
		}
		i++;
	}

	return 0;
}

int strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int i = 0;

	while (s1[i] != '\0' && s2[i] != '\0' && i < n) {
		if (s1[i] != s2[i]) {
			return ((s1[i] < s2[2]) ? -1 : 1);
		}
		i++;
	}

	return 0;
}

void *memcpy(void *dest, const void *src, size_t n)
{
        char *dest_c = (char *)dest;
        const char *src_c = (const char *)src;

        while (n--) {
            *dest_c++ = *src_c++;
        }
        return dest;
}

void *memset(void *s, char c, size_t n)
{
	char *s_p = (char *)s;

	for ( ; n != 0; n--) {
		*s_p++ = c;
	}

	return s;
}
