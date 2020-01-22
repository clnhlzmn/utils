#include "list.h"

int list_element_init(struct list_element *element) {
    if (!element) return -1;
    element->prev = NULL;
    element->next = NULL;
    return 0;
}

int list_element_in_list(struct list_element *element, bool *in_list) {
    if (!element || !in_list) return -1;
    *in_list = element->prev != NULL;
    return 0;
}

int list_element_insert_after(struct list_element *after, struct list_element *element) {
    bool in_list;
    if (list_element_in_list(after, &in_list) != 0 || !in_list) return -1;
    if (list_element_in_list(element, &in_list) != 0 || in_list) return -1;
    element->next = after->next;
    element->prev = after;
    after->next->prev = element;
    after->next = element;
    return 0;
}

int list_element_insert_before(struct list_element *before, struct list_element *element) {
    bool in_list;
    if (list_element_in_list(before, &in_list) != 0 || !in_list) return -1;
    if (list_element_in_list(element, &in_list) != 0 || in_list) return -1;
    element->next = before;
    element->prev = before->prev;
    before->prev->next = element;
    before->prev = element;
    return 0;
}

int list_element_remove(struct list_element *element) {
    bool in_list;
    if (list_element_in_list(element, &in_list) || !in_list) return -1;
    element->prev->next = element->next;
    element->next->prev = element->prev;
    element->next = NULL;
    element->prev = NULL;
    return 0;
}

int list_init(struct list *list) {
    if (!list) return -1;
    list->head.prev = &list->head;
    list->head.next = &list->head;
    return 0;
}

int list_is_empty(struct list *list, bool *is_empty) {
    if (!list || !is_empty) return -1;
    *is_empty = list->head.prev == &list->head;
    return 0;
}

int list_prepend(struct list *list, struct list_element *element) {
    if (!list) return -1;
    return list_element_insert_after(&list->head, element);
}

int list_append(struct list *list, struct list_element *element) {
    if (!list) return -1;
    return list_element_insert_before(&list->head, element);
}

int list_remove(struct list *list, struct list_element *element) {
    (void) list;
    return list_element_remove(element);
}

int list_iterator_init(struct list_iterator *it, struct list *list) {
    if (!it || !list) return -1;
    it->list = list;
    it->current = &list->head;
    return 0;
}

int list_iterator_next(struct list_iterator *it, struct list_element **element) {
    if (!it || !element) return -1;
    if (it->current->next == &it->list->head) return -1;
    it->current = it->current->next;
    *element = it->current;
    return 0;
}

int list_iterator_previous(struct list_iterator *it, struct list_element **element) {
    if (!it || !element) return -1;
    if (it->current->prev == &it->list->head) return -1;
    it->current = it->current->prev;
    *element = it->current;
    return 0;
}

bool list_contains(struct list *list, struct list_element *element) {
    if (!list || !element) return false;
    struct list_iterator it;
    list_iterator_init(&it, list);
    struct list_element *current;
    while (list_iterator_next(&it, &current) == 0) {
        if (current == element) return true;
    }
    return false;
}

int list_clear(struct list *list) {
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