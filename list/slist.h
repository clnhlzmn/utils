
#ifndef SLIST_H
#define SLIST_H

#include <stddef.h>
#include <stdbool.h>

/*members and functions marked SLIST_PRIVATE are not part of the list interface*/
#define SLIST_PRIVATE

struct slist_element {
    SLIST_PRIVATE struct slist_element *next;
};

/*
initialize a slist_element
*/
static inline int slist_element_init(struct slist_element *element) {
    if (!element) return -1;
    element->next = NULL;
    return 0;
}

/*
causes 'element' to succeed 'after' in the list that 'after' is a member of
returns 0 if the insert was successful
*/
static inline int slist_element_insert_after(struct slist_element *after, struct slist_element *element) {
    if (!after || !element) return -1;
    element->next = after->next;
    after->next = element;
    return 0;
}

/*
removes the element following after
returns 0 if an element was removed
*/
static inline int slist_element_remove_after(struct slist_element *after) {
    if (!after) return -1;
    if (!after->next) return 0;
    after->next = after->next->next;
    return 0;
}

struct slist {
    SLIST_PRIVATE struct slist_element head;
};

/*
initialize a list
returns 0 if successful
*/
static inline int slist_init(struct slist *list) {
    if (!list) return -1;
    return slist_element_init(&list->head);
}

/*
checks if a list is empty
return 0 if the check was successful
is_empty is used to store the result
*/
static inline int slist_is_empty(struct slist *list, bool *is_empty) {
    if (!list || !is_empty) return -1;
    *is_empty = list->head.next == NULL;
    return 0;
}

/*
prepends element to list
return 0 if successful
if element is already part of a list then the result is undefined
*/
static inline int slist_prepend(struct slist *list, struct slist_element *element) {
    if (!list) return -1;
    return slist_element_insert_after(&list->head, element);
}

/*
appends element to list
return 0 if successful
if element is already part of a list then the result is undefined
*/
static inline int slist_append(struct slist *list, struct slist_element *element) {
    if (!list || !element) return -1;
    struct slist_element *last = &list->head;
    while (last->next) {
        last = last->next;
    }
    return slist_element_insert_after(last, element);
}

/*
removes element from list
return 0 if successful
if element is a member of a list other than the first argument then the effect is undefined
*/
static inline int slist_remove(struct slist *list, struct slist_element *element) {
    if (!list || !element) return -1;
    struct slist_element *last = &list->head;
    while (last->next) {
        if (last->next == element)
            break;
        last = last->next;
    }
    if (!last->next) return -1;
    return slist_element_remove_after(last);
}

/*
removes head element from list
element pointer is set to head element if remove is successful
return 0 if successful
*/
static inline int slist_remove_head(struct slist *list, struct slist_element **element) {
    if (!element) return -1;
    bool is_empty;
    if (slist_is_empty(list, &is_empty) || is_empty) return -1;
    *element = list->head.next;
    return slist_element_remove_after(&list->head);
}

struct slist_iterator {
    SLIST_PRIVATE struct slist_element *current;
};

/*
initialize a list iterator
return 0 if successful
*/
static inline int slist_iterator_init(struct slist_iterator *it, struct slist *list) {
    if (!it || !list) return -1;
    it->current = &list->head;
    return 0;
}

/*
gets the next element from an iterator
return 0 if successful
element is used to store the next element
*/
static inline int slist_iterator_next(struct slist_iterator *it, struct slist_element **element) {
    if (!it || !element) return -1;
    if (!it->current->next) return -1;
    it->current = it->current->next;
    *element = it->current;
    return 0;
}

#endif //SLIST_H