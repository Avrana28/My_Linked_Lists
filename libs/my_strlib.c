#include "my_strlib.h"

size_t my_strlen( const char s[]) {
    const char *ptr = s;
    while ( *ptr != '\0' ) {
        ptr++;
    }
    return ptr - s;
}
char* my_strcpy(char *dest, const char *src) {
    char *ptr = dest;
    while (*src != '\0') {
        *dest = *src;
        dest++;
        src++;
    }
    *dest = '\0';

    return ptr;
}

int my_strcmp(const char *s1, const char *s2) {
    while (*s1 != '\0' && *s2 != '\0') {
        if (*s1 < *s2) {
            return -1;
        }
        if (*s1 > *s2) {
            return 1;
        }
        s1++;
        s2++;
    }

    if (*s1 < *s2) {
        return -1;
    }
    if (*s1 > *s2) {
        return 1;
    }
    return 0;
}
