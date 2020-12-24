#include <stddef.h>
#include "string_split.h"

int string_split_init(struct string_split_iterator *it, const volatile char *input, char delimiter) {
    if (!it) return -1;
    if (!input) return -1;
    it->begin = NULL;
    it->end = input;
    it->delimiter = delimiter;
    return 0;
}

int string_split_next(struct string_split_iterator *it) {
    if (!it) return -1;
    if (*it->end == 0) {
        /*reached the end*/
        return -1;
    }
    if (it->begin == NULL && *it->end == it->delimiter) {
        /*empty range at beginning*/
        it->begin = it->end;
        return 0;
    }
    if (it->begin != NULL) {
        it->end++;
    }
    it->begin = it->end;
    while (*it->end && *it->end != it->delimiter)
        it->end++;      
    return 0;
}
