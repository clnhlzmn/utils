
#ifndef POOL_H
#define POOL_H

#include <stddef.h>
#include <stdbool.h>
#include "slist.h"

#define POOL(name, type, size)                                                  \
struct pool_##name {                                                            \
    struct pool_##name##_private {                                              \
        struct slist_element element;                                           \
        type data;                                                              \
    };                                                                          \
    struct slist free_list;                                                     \
    struct pool_##name##_private items[size];                                   \
};                                                                              \
static inline int pool_##name##_init(struct pool_##name *self) {                \
    if (!self) return -1;                                                       \
    slist_init(&self->free_list);                                               \
    for (size_t i = 0; i < size; ++i) {                                         \
        slist_prepend(&self->free_list, &self->items[i].element);               \
    }                                                                           \
    return 0;                                                                   \
}                                                                               \
static inline type *pool_##name##_alloc(struct pool_##name *self) {             \
    if (!self) return NULL;                                                     \
    struct slist_element *head;                                                 \
    if (slist_remove_head(&self->free_list, &head))                             \
        return NULL;                                                            \
    struct pool_##name##_private *item = (struct pool_##name##_private *)       \
        (((char *)head) - offsetof(struct pool_##name##_private, element));     \
    return &item->data;                                                         \
}                                                                               \
static inline void pool_##name##_free(struct pool_##name *self, type *obj) {    \
    if (!self || !obj) return;                                                  \
    struct pool_##name##_private *item = (struct pool_##name##_private *)       \
        (((char *)obj) - offsetof(struct pool_##name##_private, data));         \
    slist_prepend(&self->free_list, &item->element);                            \
}

#endif //POOL_H