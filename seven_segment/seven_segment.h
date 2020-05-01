/**
\file seven_segment.h
\brief ascii to seven segment encoding
\details These encoding functions assume the standard 
seven segment layout and the bit ordering given below
*/

#ifndef SEVEN_SEGMENT_H_
#define SEVEN_SEGMENT_H_

#include <stddef.h>
#include <stdint.h>

/**
\brief bit positions for encoded characters
*/
enum seven_segment_bit_positions {
    SEGMENT_G = 0,
    SEGMENT_F = 1,
    SEGMENT_E = 2,
    SEGMENT_D = 3,
    SEGMENT_C = 4,
    SEGMENT_B = 5,
    SEGMENT_A = 6,
    SEGMENT_DP = 7
};

/**
\brief encode a single character
\param c character to encode. Valid inputs are 0-9, a-z, A-Z, -, and .
\return the encoded character
*/
uint8_t seven_segment_encode_char(char c);

/**
\brief encode a string
\param dst destination buffer
\param size destination buffer size
\param str source string
\return the number of bytes written to \p dst
\details Will encode \p str and write the result to \p dst. Encoded size will be no more than
the length of \p str but may be less. Most characters are mapped one to one with their encoded form,
but decimal points get attached to the previous character if applicable.
*/
size_t seven_segment_encode(uint8_t *dst, size_t size, const char *str);

#endif /* SEVEN_SEGMENT_H_ */