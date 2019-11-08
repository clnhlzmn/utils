/*
 * event.h
 *
 * Created: 11/8/2019 8:56:52 AM
 *  Author: Colin
 */ 


#ifndef EVENT_H_
#define EVENT_H_

#include "list.h"

#define CONTAINER_OF(ptr, type, field_name) ((type *)(((char *)ptr) - offsetof(type, field_name)))

struct event {
    struct list handlers;
};

struct event_handler {
    struct list_element element;
    void (*fun)(struct event *evt, void *ctx);
};

static inline int event_handler_init(struct event_handler *handler, void (*fun)(struct event *, void *)) {
    if (!handler) return -1;
    list_element_init(&handler->element);
    handler->fun = fun;
    return 0;
}

static inline int event_init(struct event *evt) {
    if (!evt) return -1;
    list_init(&evt->handlers);
    return 0;
}

static inline int event_subscribe(struct event *evt, struct event_handler *handler) {
    if (!evt || !handler) return -1;
    return list_append(&evt->handlers, &handler->element);
}

static inline int event_unsubscribe(struct event *evt, struct event_handler *handler) {
    if (!evt || !handler) return -1;
    return list_remove_safe(&evt->handlers, &handler->element);
}

static inline int event_dispatch(struct event *evt, void *ctx) {
    if (!evt) return -1;
    struct list_iterator it;
    list_iterator_init(&it, &evt->handlers);
    struct list_element *element;
    while (list_iterator_next(&it, &element) == 0) {
        struct event_handler *handler = CONTAINER_OF(element, struct event_handler, element);
        if (handler->fun) handler->fun(evt, ctx);
    }
    return 0;
}

#endif /* EVENT_H_ */