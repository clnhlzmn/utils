#ifndef STRING_SPLIT_H
#define STRING_SPLIT_H

struct string_split_iterator {
    /*Points to the beginning of the range between delimiters*/
    const volatile char *begin;
    /*Points to one character past the end of the range between delimiters*/
    const volatile char *end;
    /*The delimiter character*/
    char delimiter;
};

/*Initializes a struct string_split_iterator.
Parameter input should point to a null terminated string.
Parameter delimiter is the character by which to split the string*/
int string_split_init(struct string_split_iterator *it, const volatile char *input, char delimiter);

/*Finds the next range between two delimiter characters, or the next range 
between the beginning or end of the input string and one delimiter and 
returns 0. If such a range is found then the begin and end fields of it are
updated to point to the beginning and one past the end of the range, respectively.
If there is no such range then a number other than 0 is returned and it is not changed.*/
int string_split_next(struct string_split_iterator *it);

#endif /*STRING_SPLIT_H*/
