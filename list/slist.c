#include "slist.h"

int slist_element_init(struct slist_element *element) {
    if (!element) return -1;
    element->next = NULL;
    return 0;
}

int slist_element_insert_after(struct slist_element *after, struct slist_element *element) {
    if (!after || !element) return -1;
    element->next = after->next;
    after->next = element;
    return 0;
}

int slist_element_remove_after(struct slist_element *after) {
    if (!after) return -1;
    if (!after->next) return 0;
    after->next = after->next->next;
    return 0;
}

int slist_init(struct slist *list) {
    if (!list) return -1;
    return slist_element_init(&list->head);
}

int slist_is_empty(struct slist *list, bool *is_empty) {
    if (!list || !is_empty) return -1;
    *is_empty = list->head.next == NULL;
    return 0;
}

int slist_prepend(struct slist *list, struct slist_element *element) {
    if (!list) return -1;
    return slist_element_insert_after(&list->head, element);
}

int slist_append(struct slist *list, struct slist_element *element) {
    if (!list || !element) return -1;
    struct slist_element *last = &list->head;
    while (last->next) {
        last = last->next;
    }
    return slist_element_insert_after(last, element);
}

int slist_remove(struct slist *list, struct slist_element *element) {
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

int slist_remove_head(struct slist *list, struct slist_element **element) {
    if (!element) return -1;
    bool is_empty;
    if (slist_is_empty(list, &is_empty) || is_empty) return -1;
    *element = list->head.next;
    return slist_element_remove_after(&list->head);
}

int slist_iterator_init(struct slist_iterator *it, struct slist *list) {
    if (!it || !list) return -1;
    it->current = &list->head;
    return 0;
}

int slist_iterator_next(struct slist_iterator *it, struct slist_element **element) {
    if (!it || !element) return -1;
    if (!it->current->next) return -1;
    it->current = it->current->next;
    *element = it->current;
    return 0;
}