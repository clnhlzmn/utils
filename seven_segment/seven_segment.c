/*
 * seven_segment.c
 *
 * Created: 11/5/2019 10:07:14 AM
 *  Author: Colin
 */ 

#include <stdbool.h>
#include "seven_segment.h"

static uint8_t seven_segment_numerals(char n) {
    static uint8_t numerals[10] = {
        0x7E, /*0*/
        0x30, /*1*/
        0x6D, /*2*/
        0x79, /*3*/
        0x33, /*4*/
        0x5B, /*5*/
        0x5F, /*6*/
        0x70, /*7*/
        0x7F, /*8*/
        0x7B /*9*/
    };
    return numerals[n - '0'];
}

static uint8_t seven_segment_lower(char c) {
    static uint8_t lower_case_alpha[26] = {
        0x7D, /*a*/
        0x1F, /*b*/
        0x0D, /*c*/
        0x3D, /*d*/
        0x6F, /*e*/
        0x47, /*f*/
        0x7B, /*g*/
        0x17, /*h*/
        0x10, /*i*/
        0x18, /*j*/
        0x57, /*K*/
        0x06, /*l*/
        0x54, /*M*/
        0x15, /*n*/
        0x1D, /*o*/
        0x67, /*P*/
        0x6B, /*q*/
        0x05, /*r*/
        0x5A, /*S*/
        0x0F, /*t*/
        0x1C, /*u*/
        0x1C, /*V*/
        0x2A, /*W*/
        0x37, /*X*/
        0x2B, /*Y*/
        0x6C /*Z*/
    };
    return lower_case_alpha[c - 'a'];
}

static uint8_t seven_segment_upper(char c) {
    static uint8_t upper_case_alpha[26] = {
        0x77, /*A*/
        0x7F, /*B*/
        0x4E, /*C*/
        0x78, /*D*/
        0x4F, /*E*/
        0x47, /*F*/
        0x5E, /*G*/
        0x37, /*H*/
        0x30, /*I*/
        0x38, /*J*/
        0x57, /*K*/
        0x0E, /*L*/
        0x54, /*M*/
        0x76, /*N*/
        0x7E, /*O*/
        0x67, /*P*/
        0x6B, /*q*/
        0x46, /*R*/
        0x5A, /*S*/
        0x0F, /*t*/
        0x3E, /*U*/
        0x3E, /*V*/
        0x2A, /*W*/
        0x37, /*X*/
        0x3B, /*Y*/
        0x6C /*Z*/
    };
    return upper_case_alpha[c - 'A'];
}

uint8_t seven_segment_encode_char(char c) {
    if (c >= '0' && c <= '9') {
        return seven_segment_numerals(c);
    } else if (c >= 'a' && c <= 'z') {
        return seven_segment_lower(c);
    } else if (c >= 'A' && c <= 'Z') {
        return seven_segment_upper(c);
    } else if (c == '.') {
        return 0x80;
    } else if (c == '-') {
        return 0x01;
    } else {
        return 0;
    }
}

static bool dp_set(char c) {
    return c & 0x80;
}

size_t seven_segment_encode(uint8_t *out, size_t out_size, const char *in) {
    size_t count = 0;
    for (char c = *in; c; c = *++in) {
        uint8_t encoded = seven_segment_encode_char(c);
        if (c == '.') {
            if (count == 0 && count < out_size) {
                out[count++] = encoded;
            } else if (count < out_size && dp_set(out[count - 1])) {
                out[count++] = encoded;
            } else if (count > 0 && !dp_set(out[count - 1])) {
                out[count - 1] |= encoded;
            } else {
                break;
            }
        } else if (count < out_size) {
            out[count++] = encoded;
        } else {
            break;
        }
    }
    return count;
}

