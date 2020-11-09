#ifndef MAJORITY_H
#define MAJORITY_H

#include <stdint.h>
#include <stdbool.h>

static inline uint8_t majority_3(uint8_t a, uint8_t b, uint8_t c) {
    return (a & b & c) | (~a & b & c) | (a & ~b & c) | (a & b & ~c);
}

static inline uint8_t majority_5(
    uint8_t a, uint8_t b, uint8_t c, uint8_t d, uint8_t e) {
    return ( a &  b &  c &  d &  e) | 
           (~a &  b &  c &  d &  e) | 
           ( a & ~b &  c &  d &  e) | 
           ( a &  b & ~c &  d &  e) | 
           ( a &  b &  c & ~d &  e) | 
           ( a &  b &  c &  d & ~e) | 
           (~a & ~b &  c &  d &  e) | 
           (~a &  b & ~c &  d &  e) | 
           (~a &  b &  c & ~d &  e) | 
           (~a &  b &  c &  d & ~e) | 
           ( a & ~b & ~c &  d &  e) | 
           ( a & ~b &  c & ~d &  e) | 
           ( a & ~b &  c &  d & ~e) | 
           ( a &  b & ~c & ~d &  e) | 
           ( a &  b & ~c &  d & ~e) | 
           ( a &  b &  c & ~d & ~e);
}

#endif /*MAJORITY_H*/
