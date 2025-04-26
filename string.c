// SPDX-License-Identifier: BSD-3-Clause

#include <string.h>

char *strcpy(char *destination, const char *source)
{
	char *dest = destination;
    while ((*dest++ = *source++) != '\0');
    return destination;
}

char *strncpy(char *destination, const char *source, size_t len)
{
	size_t i;
	for (i = 0; i < len && source[i] != '\0'; i++)
		destination[i] = source[i];
	for (; i < len; i++)
		destination[i] = '\0';
	return destination;
}

char *strcat(char *destination, const char *source) {
    char *dest = destination;
    while (*dest != '\0')
        dest++;
    while ((*dest++ = *source++) != '\0');
    return destination;
}


char *strncat(char *destination, const char *source, size_t len)
{
	char *dest = destination;
    while (*dest != '\0')
        dest++;
    while (len-- > 0 && *source != '\0')
        *dest++ = *source++;
    *dest = '\0';
    return destination;
}

int strcmp(const char *str1, const char *str2)
{
	int i = 0;
    while (str1[i] != '\0' && str2[i] != '\0') {
        if (str1[i] != str2[i])
            return (unsigned char)str1[i] - (unsigned char)str2[i];
        i++;
    }
    return (unsigned char)str1[i] - (unsigned char)str2[i];
}

int strncmp(const char *str1, const char *str2, size_t len)
{
	size_t i = 0;
    while (i < len && str1[i] != '\0' && str2[i] != '\0') {
        if (str1[i] != str2[i])
            return (unsigned char)str1[i] - (unsigned char)str2[i];
        i++;
    }
    if (i == len)
        return 0;
    return (unsigned char)str1[i] - (unsigned char)str2[i];
}

size_t strlen(const char *str)
{
	size_t i = 0;
    while (*str != '\0') {
        str++;
        i++;
    }
    return i;
}

char *strchr(const char *str, int c)
{
	while (*str != '\0') {
        if (*str == (char)c)
            return (char *)str;
        str++;
    }
    if (*str == (char)c)
        return (char *)str;
    return NULL;
}

char *strrchr(const char *str, int c)
{
	const char *ult = NULL;
    while (*str != '\0') {
        if (*str == (char)c)
            ult = str;
        str++;
    }
    if (c == '\0')
        return (char *)str;
    return (char *)ult;
}

char *strstr(const char *haystack, const char *needle)
{
	size_t i, j;
    if (*needle == '\0')
        return (char *)haystack;
    for (i = 0; haystack[i] != '\0'; i++) {
        for (j = 0; needle[j] != '\0' && haystack[i + j] == needle[j]; j++);
        if (needle[j] == '\0')
            return (char *)&haystack[i];
    }
    return NULL;
}

char *strrstr(const char *haystack, const char *needle)
{
	if (*needle == '\0')
        return (char *)haystack;
    const char *ult = NULL;
    size_t l = strlen(needle);
    while (*haystack) {
        if (strncmp(haystack, needle, l) == 0)
            ult = haystack;
        haystack++;
    }
    return (char *)ult;
}

void *memcpy(void *destination, const void *source, size_t num)
{
	char *dest = (char *)destination;
    const char *sur = (const char *)source;
    for (size_t i = 0; i < num; i++)
        dest[i] = sur[i];
    return destination;
}

void *memmove(void *destination, const void *source, size_t num)
{
	char *dest = (char *)destination;
    const char *sur = (const char *)source;
    if (dest < sur || dest >= sur + num) {
        for (size_t i = 0; i < num; i++)
            dest[i] = sur[i];
    } else {
        for (size_t i = num; i > 0; i--)
            dest[i - 1] = sur[i - 1];
    }
    return destination;
}

int memcmp(const void *ptr1, const void *ptr2, size_t num)
{
	const unsigned char *p1 = (const unsigned char *)ptr1;
    const unsigned char *p2 = (const unsigned char *)ptr2;
    for (size_t i = 0; i < num; i++) {
        if (p1[i] != p2[i])
            return p1[i] - p2[i];
    }
    return 0;
}

void *memset(void *source, int value, size_t num)
{
	unsigned char *p = (unsigned char *)source;
    for (size_t i = 0; i < num; i++)
        p[i] = (unsigned char)value;
    return source;
}
