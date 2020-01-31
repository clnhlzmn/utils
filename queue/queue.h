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
static inline int queue_##name##_init(volatile struct queue_##name *self) {             \
    if (!self) return -1;                                                               \
    self->read = 0;                                                                     \
    self->write = 0;                                                                    \
    self->count = 0;                                                                    \
    return 0;                                                                           \
}                                                                                       \
static inline int queue_##name##_push(volatile struct queue_##name *self,               \
                                      const volatile type *item) {                      \
    if (!self || !item) return -1;                                                      \
    if (self->count < size) {                                                           \
        size_t next = (self->write + 1) % size;                                         \
        self->storage[next] = *item;                                                    \
        self->write = next;                                                             \
        self->count++;                                                                  \
        return 0;                                                                       \
    } else {                                                                            \
        return -1;                                                                      \
    }                                                                                   \
}                                                                                       \
static inline int queue_##name##_pop(volatile struct queue_##name *self,                \
                                     volatile type *item) {                             \
    if (!self || !item) return -1;                                                      \
    if (self->count > 0) {                                                              \
        size_t next = (self->read + 1) % size;                                          \
        *item = self->storage[next];                                                    \
        self->read = next;                                                              \
        self->count--;                                                                  \
        return 0;                                                                       \
    } else {                                                                            \
        return -1;                                                                      \
    }                                                                                   \
}                                                                                       \
static inline size_t queue_##name##_count(const volatile struct queue_##name *self) {   \
    if (!self) return 0;                                                                \
    return self->count;                                                                 \
}                                                                                       \
static inline void queue_##name##_foreach(volatile struct queue_##name *self,           \
                                          int (*fun)(volatile type *, volatile void *), \
                                          volatile void *ctx) {                         \
    if (!self) return;                                                                  \
    if (fun == NULL) return;                                                            \
    for (size_t i = 0; i < self->count; ++i) {                                          \
        if (fun(&self->storage[(self->read + i + 1) % size], ctx) != 0) break;          \
    }                                                                                   \
}

#ifdef DOXYGEN
QUEUE(NAME, TYPE, SIZE);
/**
\struct queue_NAME
\brief instance type generated by \ref QUEUE with \c name set to \a NAME, \c type set to \a TYPE, and \c size set to \a SIZE

\var queue_NAME::storage
\brief PRIVATE \n an array for storing elements in the queue

\var queue_NAME::read 
\brief PRIVATE \n index to the next item to be read

\var queue_NAME::write
\brief PRIVATE \n index to the next location to write an item

\var queue_NAME::count
\brief PRIVATE \n the number of items in the queue

\fn int queue_NAME_init(volatile struct queue_NAME *self)
\brief init function generated by \ref QUEUE with \c name set to \a NAME, \c type set to \a TYPE, and \c size set to \a SIZE
\param self the \ref queue_NAME to initialize
\return 0 if successful

\fn int queue_NAME_push(volatile struct queue_NAME *self, const volatile TYPE *item)
\brief push an item onto the queue
\param self the \ref queue_NAME on which to push the item
\param item pointer to the item to push
\return 0 if successful

\fn int queue_NAME_pop(volatile struct queue_NAME *self, volatile TYPE *item)
\brief pop an item from the queue
\param self the \ref queue_NAME from which to pop the item
\param item pointer the location to which the item should be copied
\return 0 if successful

\fn size_t queue_NAME_count(const volatile struct queue_NAME *self)
\brief get the number of items in the queue
\param self the \ref queue_NAME from which to get the item count
\return the item count

\fn void queue_NAME_foreach(volatile struct queue_NAME *self, int (*fun)(volatile TYPE *, volatile void *), volatile void *ctx)
\brief calls \c fun for each item in the queue
\param self the queue to traverse
\param fun a function pointer that takes a pointer to \a TYPE and a pointer to void \n 
if \c fun returns 0 then the traversal will continue otherwise it will stop
\param ctx a pointer to arbitrary context that gets passed as the second argument to \c fun for each item in the queue

*/
#endif


#endif //QUEUE_H

