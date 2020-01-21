/**
\file list.h
\brief An intrusive circular doubly linked list.
*/
#ifndef LIST_H
#define LIST_H

#include <stddef.h>
#include <stdbool.h>

/**
\brief list element state
\details embed a \ref list_element member in a struct that will be a member of a \ref list
*/
struct list_element {
    /**\brief pointer to last element*/
    struct list_element *prev;
    /**\brief pointer to next element*/
    struct list_element *next;
};

/**
\brief initialize a list_element
\param element pointer to \ref list_element
\return 0 if successful
*/
static inline int list_element_init(struct list_element *element) {
    if (!element) return -1;
    element->prev = NULL;
    element->next = NULL;
    return 0;
}

/**
\brief checks if an element is in a list
\param element the element to check for list membership
\param[out] in_list pointer to location where result should be written
\return 0 if successful
*/
static inline int list_element_in_list(struct list_element *element, bool *in_list) {
    if (!element || !in_list) return -1;
    *in_list = element->prev != NULL;
    return 0;
}

/**
\brief insert an element after another
\param after list element after which to insert
\param element element to insert
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

/**
\brief insert an element before another
\param before element before which to insert
\param element element to insert
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

/**
\brief removes \p element from a list
\param element \ref list_element to remove
\return 0 if successful
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

/**
\brief list state
*/
struct list {
    /**\brief pseudo head \ref list_element*/
    struct list_element head;
};

/**
\brief initialize a list
\param list pointer to \ref list
\return 0 if successful
*/
static inline int list_init(struct list *list) {
    if (!list) return -1;
    list->head.prev = &list->head;
    list->head.next = &list->head;
    return 0;
}

/**
\brief checks if a list is empty
\param list pointer to initialized \ref list
\param[out] is_empty pointer to location where result should be written
\return 0 if the check was successful
*/
static inline int list_is_empty(struct list *list, bool *is_empty) {
    if (!list || !is_empty) return -1;
    *is_empty = list->head.prev == &list->head;
    return 0;
}

/**
\brief prepends an element to a list
\param list pointer to the list on which to prepend
\param element pointer to element to prepend
\return 0 if successful
*/
static inline int list_prepend(struct list *list, struct list_element *element) {
    if (!list) return -1;
    return list_element_insert_after(&list->head, element);
}

/**
\brief appends an element to a list
\param list pointer to the list to append to
\param element pointer to the element to append
\return 0 if successful
*/
static inline int list_append(struct list *list, struct list_element *element) {
    if (!list) return -1;
    return list_element_insert_before(&list->head, element);
}

/**
\brief removes an element from a list
\note removing the current element of an iterator will invalidate that iterator
\param list the list from which to remove
\param element the element to remove
\return 0 if successful
*/
static inline int list_remove(struct list *list, struct list_element *element) {
    (void) list;
    return list_element_remove(element);
}

/**
\brief list iterator state
*/
struct list_iterator {
    /**\brief the list which this iterator points to*/
    struct list *list;
    /**\brief the current element*/
    struct list_element *current;
};

/**
\brief initialize a list iterator
\details the iterator will point to one before the first element of \p list or, equivalently, to one after the last element of \p list
\param it pointer to the iterator to initialize
\param list pointer to the list over which to iterate
\return 0 if successful
*/
static inline int list_iterator_init(struct list_iterator *it, struct list *list) {
    if (!it || !list) return -1;
    it->list = list;
    it->current = &list->head;
    return 0;
}

/**
\brief gets the next element from an iterator
\param it the iterator from which to get the next element
\param[out] element pointer to a location where the next element pointer should be written
\return 0 if successful
*/
static inline int list_iterator_next(struct list_iterator *it, struct list_element **element) {
    if (!it || !element) return -1;
    if (it->current->next == &it->list->head) return -1;
    it->current = it->current->next;
    *element = it->current;
    return 0;
}

/**
\brief gets the previous element from an iterator
\param it the iterator from which to get the previous element
\param[out] element pointer to a location where the previous element pointer should be written
\return 0 if successful
*/
static inline int list_iterator_previous(struct list_iterator *it, struct list_element **element) {
    if (!it || !element) return -1;
    if (it->current->prev == &it->list->head) return -1;
    it->current = it->current->prev;
    *element = it->current;
    return 0;
}

/**
\brief checks if an element is contained in a list
\param list the list to check
\param element the element to look for
\return true if \p element is in \p list, false otherwise
*/
static inline bool list_contains(struct list *list, struct list_element *element) {
    if (!list || !element) return false;
    struct list_iterator it;
    list_iterator_init(&it, list);
    struct list_element *current;
    while (list_iterator_next(&it, &current) == 0) {
        if (current == element) return true;
    }
    return false;
}

/**
\brief removes all elments from a list
\param list the list to clear
\return 0 if all elements were removed
*/
static inline int list_clear(struct list *list) {
    if (!list) return -1;
    struct list_iterator it;
    list_iterator_init(&it, list);
    struct list_element *last = NULL;
    struct list_element *elem;
    while (list_iterator_next(&it, &elem) == 0) {
        if (last != NULL) {
            list_remove(list, last);
        }
        last = elem;
    }
    if (last != NULL) {
        list_remove(list, last);
    }
    return 0;
}

#endif //LIST_H