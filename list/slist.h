/**
\file slist.h
\brief An intrusive singly linked list.
*/

#ifndef SLIST_H
#define SLIST_H

#include <stddef.h>
#include <stdbool.h>

/**
\brief slist element state
\details embed \ref slist_element in structs that will be elements of an \ref slist
*/
struct slist_element {
    /**\brief pointer to next element*/
    struct slist_element *next;
};

/**
\brief initialize a slist_element
\param element pointer to element to initialize
\return 0 if successful
*/
static inline int slist_element_init(struct slist_element *element) {
    if (!element) return -1;
    element->next = NULL;
    return 0;
}

/**
\brief insert an element after another
\param after the element after which to insert
\param element the element to insert
\return 0 if the insert was successful
*/
static inline int slist_element_insert_after(struct slist_element *after, struct slist_element *element) {
    if (!after || !element) return -1;
    element->next = after->next;
    after->next = element;
    return 0;
}

/**
\brief removes an element following another
\param after the element after which to remove
\return 0 if an element was removed
*/
static inline int slist_element_remove_after(struct slist_element *after) {
    if (!after) return -1;
    if (!after->next) return 0;
    after->next = after->next->next;
    return 0;
}

/**
\brief slist state
*/
struct slist {
    /**\brief pseudo head element*/
    struct slist_element head;
};

/**
\brief initialize an \ref slist
\param list the \ref slist to initialize
\return 0 if successful
*/
static inline int slist_init(struct slist *list) {
    if (!list) return -1;
    return slist_element_init(&list->head);
}

/**
\brief checks if a list is empty
\param list the list to check
\param[out] is_empty pointer to location where result should be stored
\return 0 if the check was successful
*/
static inline int slist_is_empty(struct slist *list, bool *is_empty) {
    if (!list || !is_empty) return -1;
    *is_empty = list->head.next == NULL;
    return 0;
}

/**
\brief prepends element to list
\param list the list on which to prepend
\param element the element to prepend
\return 0 if successful
\details If \p element is part of a list then that list will be corrupted.
*/
static inline int slist_prepend(struct slist *list, struct slist_element *element) {
    if (!list) return -1;
    return slist_element_insert_after(&list->head, element);
}

/**
\brief appends an element to a list
\param list the list on which to append
\param element the element to append
\return 0 if successful
\details If \p element is part of a list then that list will be corrupted.
The runtime of this function is linear in the length of \p list.
*/
static inline int slist_append(struct slist *list, struct slist_element *element) {
    if (!list || !element) return -1;
    struct slist_element *last = &list->head;
    while (last->next) {
        last = last->next;
    }
    return slist_element_insert_after(last, element);
}

/**
\brief removes an element from a list
\param list the list from which to remove
\param element the element to remove
\return 0 if successful
\details If \p element is a member of a list other than \p list then the other list will be corrupted.
The runtime of this function is linear in the length of \p list.
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

/**
\brief removes the first element from a list
\param list the list from which to remove
\param[out] element location where the removed element should be stored
\return 0 if an element was removed
*/
static inline int slist_remove_head(struct slist *list, struct slist_element **element) {
    if (!element) return -1;
    bool is_empty;
    if (slist_is_empty(list, &is_empty) || is_empty) return -1;
    *element = list->head.next;
    return slist_element_remove_after(&list->head);
}

/**
\brief slist iterator state
*/
struct slist_iterator {
    /**\brief pointer to current element*/
    struct slist_element *current;
};

/**
\brief initialize a list iterator
\param it the iterator to initialize
\param list the list over which to iterate
\return 0 if successful
*/
static inline int slist_iterator_init(struct slist_iterator *it, struct slist *list) {
    if (!it || !list) return -1;
    it->current = &list->head;
    return 0;
}

/**
\brief gets the next element from an iterator
\param it the iterator from which to get the next element
\param[out] element the location at which to store the next element
\return 0 if successful
*/
static inline int slist_iterator_next(struct slist_iterator *it, struct slist_element **element) {
    if (!it || !element) return -1;
    if (!it->current->next) return -1;
    it->current = it->current->next;
    *element = it->current;
    return 0;
}

#endif //SLIST_H