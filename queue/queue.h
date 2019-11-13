/**
\file queue.h
\brief A generic FIFO queue.
*/

#ifndef QUEUE_H
#define QUEUE_H

#include <stdlib.h>
#include <stdint.h>

/*
A very simple circular buffer.

Example:
QUEUE(test, int, count)

Creates:
struct queue_test {...};
static inline void queue_test_init(struct queue_test *) {...}
static inline int queue_test_push(struct queue_test *, int *) {...}
static inline int queue_test_pop(struct queue_test *, int *) {...}

API:
queue_*_init initializes a queue
queue_*_push pushes an item onto the queue, returns 0 if successful, not 0 if fail
queue_*_pop pops an item from the queue, returns 0 if successful, not 0 if fail
queue_*_foreach takes a function pointer and pointer to some context and for each
    element in the queue calls the function with a pointer to that element. If the
    returns zero queue_*_foreach will continue processing the rest of the items, if
    the function returns non zero then queue_*_foreach will not process any more items.

*/

/**
\brief Generates the queue api
\param name a name for the api with the given type and size
\param type the type of data to store in the queue
\param size the max number of data elements
*/
#define QUEUE(name, type, size)                                                         \
struct queue_##name {                                                                   \
    type storage[size];                                                                 \
    /*index of the read head, initialy 0*/                                              \
    size_t read;                                                                        \
    /*index of the write head, initialy 0*/                                             \
    size_t write;                                                                       \
    /*number of items in the queue*/                                                    \
    size_t count;                                                                       \
};                                                                                      \
static inline void queue_##name##_init(volatile struct queue_##name *q) {               \
    q->read = 0;                                                                        \
    q->write = 0;                                                                       \
    q->count = 0;                                                                       \
}                                                                                       \
static inline int queue_##name##_push(volatile struct queue_##name *q,                  \
                                      const volatile type *item) {                      \
    if (q->count < size) {                                                              \
        size_t next = (q->write + 1) % size;                                            \
        q->storage[next] = *item;                                                       \
        q->write = next;                                                                \
        q->count++;                                                                     \
        return 0;                                                                       \
    } else {                                                                            \
        return -1;                                                                      \
    }                                                                                   \
}                                                                                       \
static inline int queue_##name##_pop(volatile struct queue_##name *q,                   \
                                     volatile type *item) {                             \
    if (q->count > 0) {                                                                 \
        size_t next = (q->read + 1) % size;                                             \
        *item = q->storage[next];                                                       \
        q->read = next;                                                                 \
        q->count--;                                                                     \
        return 0;                                                                       \
    } else {                                                                            \
        return -1;                                                                      \
    }                                                                                   \
}                                                                                       \
static inline size_t queue_##name##_count(const volatile struct queue_##name *q) {      \
    return q->count;                                                                    \
}                                                                                       \
static inline void queue_##name##_foreach(volatile struct queue_##name *q,              \
                                          int (*fun)(volatile type *, volatile void *), \
                                          volatile void *ctx) {                         \
    if (fun == NULL) return;                                                            \
    for (size_t i = 0; i < q->count; ++i) {                                             \
        if (fun(&q->storage[(q->read + i + 1) % size], ctx) != 0) break;                \
    }                                                                                   \
}


#endif //QUEUE_H

