#include <stdio.h>
#include "str.h"

char * my_strcpy(char * restrict  destination, const char * restrict source) {
    char * start =  destination;
    while (*source) {
        *destination = *source;
        ++destination;
        ++source;
    }
    *destination = '\0';
    return start;
}

char * my_strcat(char * restrict destination, const char * restrict source) {
    char * start =  destination;
    while (*destination) {
        ++destination;
    }
    while (*source) {
       *destination = *source;
       ++destination;
       ++source;
    }
    return start;
}

int my_strcmp(const char * string1, const char * string2 ) {
    while (*string2 && *string1 == *string2) {
        ++string1;
        ++string2;
    }
    return *string1 - *string2;
}

size_t my_strlen(const char * string ) {
    size_t len = 0;
    while (*string) {
        ++len;
        ++string;
    }
    return len;
}
