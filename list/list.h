
#ifndef LIST_H
#define LIST_H

#include <stddef.h>
#include <stdbool.h>

/*members and functions marked LIST_PRIVATE are not part of the list interface*/
#define LIST_PRIVATE

struct list_element {
    LIST_PRIVATE struct list_element *prev;
    LIST_PRIVATE struct list_element *next;
};

/*
initialize a list_element
*/
static inline int list_element_init(struct list_element *element) {
    if (!element) return -1;
    element->prev = NULL;
    element->next = NULL;
    return 0;
}

/*
checks if an element is in a list
returns 0 if the check was successful
the location in_list will be used to store a bool indicating if element is in a list
*/
static inline int list_element_in_list(struct list_element *element, bool *in_list) {
    if (!element || !in_list) return -1;
    *in_list = element->prev != NULL;
    return 0;
}

/*
causes 'element' to succeed 'after' in the list that 'after' is a member of
returns 0 if the insert was successful
*/
static inline int list_element_insert_after(struct list_element *after, struct list_element *element) {
    bool in_list;
    if (list_element_in_list(after, &in_list) != 0 || !in_list) return -1;
    if (list_element_in_list(element, &in_list) != 0 || in_list) return -1;
    element->next = after->next;
    element->prev = after;
    after->next->prev = element;
    after->next = element;
    return 0;
}

/*
causes 'element' to precede 'before' in the list that 'before' is a member of
returns 0 if the insert was successful
*/
static inline int list_element_insert_before(struct list_element *before, struct list_element *element) {
    bool in_list;
    if (list_element_in_list(before, &in_list) != 0 || !in_list) return -1;
    if (list_element_in_list(element, &in_list) != 0 || in_list) return -1;
    element->next = before;
    element->prev = before->prev;
    before->prev->next = element;
    before->prev = element;
    return 0;
}

/*
removes an element from a list
returns 0 if successful
*/
static inline int list_element_remove(struct list_element *element) {
    bool in_list;
    if (list_element_in_list(element, &in_list) || !in_list) return -1;
    element->prev->next = element->next;
    element->next->prev = element->prev;
    element->next = NULL;
    element->prev = NULL;
    return 0;
}

struct list {
    LIST_PRIVATE struct list_element head;
};

/*
initialize a list
returns 0 if successful
*/
static inline int list_init(struct list *list) {
    if (!list) return -1;
    list->head.prev = &list->head;
    list->head.next = &list->head;
    return 0;
}

/*
checks if a list is empty
return 0 if the check was successful
is_empty is used to store the result
*/
static inline int list_is_empty(struct list *list, bool *is_empty) {
    if (!list || !is_empty) return -1;
    *is_empty = list->head.prev == &list->head;
    return 0;
}

/*
prepends element to list
return 0 if successful
*/
static inline int list_prepend(struct list *list, struct list_element *element) {
    if (!list) return -1;
    return list_element_insert_after(&list->head, element);
}

/*
appends element to list
return 0 if successful
*/
static inline int list_append(struct list *list, struct list_element *element) {
    if (!list) return -1;
    return list_element_insert_before(&list->head, element);
}

/*
removes element from list
return 0 if successful
if element is a member of a list other than the first argument then the effect is undefined
*/
static inline int list_remove(struct list *list, struct list_element *element) {
    (void) list;
    return list_element_remove(element);
}

struct list_iterator {
    LIST_PRIVATE struct list *list;
    LIST_PRIVATE struct list_element *current;
};

/*
initialize a list iterator
return 0 if successful
*/
static inline int list_iterator_init(struct list_iterator *it, struct list *list) {
    if (!it || !list) return -1;
    it->list = list;
    it->current = &list->head;
    return 0;
}

/*
gets the next element from an iterator
return 0 if successful
element is used to store the next element
*/
static inline int list_iterator_next(struct list_iterator *it, struct list_element **element) {
    if (!it || !element) return -1;
    if (it->current->next == &it->list->head) return -1;
    it->current = it->current->next;
    *element = it->current;
    return 0;
}

#endif //LIST_H