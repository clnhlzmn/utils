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
int slist_element_init(struct slist_element *element);

/**
\brief insert an element after another
\param after the element after which to insert
\param element the element to insert
\return 0 if the insert was successful
*/
int slist_element_insert_after(struct slist_element *after, struct slist_element *element);

/**
\brief removes an element following another
\param after the element after which to remove
\return 0 if an element was removed
*/
int slist_element_remove_after(struct slist_element *after);

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
int slist_init(struct slist *list);

/**
\brief checks if a list is empty
\param list the list to check
\param[out] is_empty pointer to location where result should be stored
\return 0 if the check was successful
*/
int slist_is_empty(struct slist *list, bool *is_empty);

/**
\brief prepends element to list
\param list the list on which to prepend
\param element the element to prepend
\return 0 if successful
\details If \p element is part of a list then that list will be corrupted.
*/
int slist_prepend(struct slist *list, struct slist_element *element);

/**
\brief appends an element to a list
\param list the list on which to append
\param element the element to append
\return 0 if successful
\details If \p element is part of a list then that list will be corrupted.
The runtime of this function is linear in the length of \p list.
*/
int slist_append(struct slist *list, struct slist_element *element);

/**
\brief removes an element from a list
\param list the list from which to remove
\param element the element to remove
\return 0 if successful
\details If \p element is a member of a list other than \p list then the other list will be corrupted.
The runtime of this function is linear in the length of \p list.
*/
int slist_remove(struct slist *list, struct slist_element *element);

/**
\brief removes the first element from a list
\param list the list from which to remove
\param[out] element location where the removed element should be stored
\return 0 if an element was removed
*/
int slist_remove_head(struct slist *list, struct slist_element **element);

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
int slist_iterator_init(struct slist_iterator *it, struct slist *list);

/**
\brief gets the next element from an iterator
\param it the iterator from which to get the next element
\param[out] element the location at which to store the next element
\return 0 if successful
*/
int slist_iterator_next(struct slist_iterator *it, struct slist_element **element);

#endif //SLIST_H