/**
\file moving_average_filter.h
\brief A generic moving average filter.
*/

#ifndef MOVING_AVERAGE_FILTER_H
#define MOVING_AVERAGE_FILTER_H

#include <stddef.h>

/**
\brief generates definitions of moving average filter types and functions
*/
#define MOVING_AVERAGE_FILTER(name, type, size)                                         \
struct maf_##name {                                                                     \
    type samples[size];                                                                 \
    size_t write;                                                                       \
    type sum;                                                                           \
    type average;                                                                       \
};                                                                                      \
static inline void maf_##name##_reset(volatile struct maf_##name *self, type value) {   \
    for (size_t i = 0; i < size; ++i) {                                                 \
        self->samples[i] = value;                                                       \
    }                                                                                   \
    self->sum = value * size;                                                           \
    self->average = value;                                                              \
}                                                                                       \
static inline void maf_##name##_init(volatile struct maf_##name *self) {                \
    self->write = 0;                                                                    \
    maf_##name##_reset(self, 0);                                                        \
}                                                                                       \
static inline type maf_##name##_input(volatile struct maf_##name *self, type input) {   \
    type oldest = self->samples[self->write];                                           \
    self->sum -= oldest;                                                                \
    self->sum += input;                                                                 \
    self->samples[self->write] = input;                                                 \
    self->write++;                                                                      \
    self->write %= size;                                                                \
    self->average = self->sum / size;                                                   \
    return self->average;                                                               \
}                                                                                       \
static inline type maf_##name##_last_output(const volatile struct maf_##name *self) {   \
    return self->average;                                                               \
}                                                                                       \
static inline type maf_##name##_last_input(const volatile struct maf_##name *self) {    \
    size_t index = (self->write - 1) % size;                                            \
    return self->samples[index];                                                        \
}

#endif //MOVING_AVERAGE_FILTER_H

