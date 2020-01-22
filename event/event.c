#include "event.h"

enum event_handler_flags {
    UNSUBSCRIBE = 1,
    ACTIVE = 2,
};

int event_handler_init(struct event_handler *handler, void (*fun)(struct event *, void *)) {
    if (!handler) return -1;
    list_element_init(&handler->element);
    handler->fun = fun;
    handler->flags = 0;
    return 0;
}

int event_init(struct event *evt) {
    if (!evt) return -1;
    list_init(&evt->handlers);
    return 0;
}

int event_subscribe(struct event *evt, struct event_handler *handler) {
    if (!evt || !handler) return -1;
    return list_prepend(&evt->handlers, &handler->element);
}

int event_unsubscribe(struct event *evt, struct event_handler *handler) {
    if (!evt || !handler) return -1;
    if (handler->flags & ACTIVE) {
        handler->flags |= UNSUBSCRIBE;
        return 0;
    } else {
        return list_remove(&evt->handlers, &handler->element);
    }
}

static void event_unsubscribe_if_flag_set(struct event *evt, struct event_handler *handler) {
    if (handler && handler->flags & UNSUBSCRIBE) {
        list_remove(&evt->handlers, &handler->element);
        handler->flags &= ~UNSUBSCRIBE;
    }
}

int event_publish(struct event *evt, void *ctx) {
    if (!evt) return -1;
    struct list_iterator it;
    list_iterator_init(&it, &evt->handlers);
    struct list_element *element;
    struct event_handler *last_handler = NULL;
    while (list_iterator_next(&it, &element) == 0) {
        struct event_handler *handler = (struct event_handler *)
            ((char*)element - offsetof(struct event_handler, element));
        handler->flags |= ACTIVE;
        if (handler->fun) handler->fun(evt, ctx);
        handler->flags &= ~ACTIVE;
        event_unsubscribe_if_flag_set(evt, last_handler);
        last_handler = handler;
    }
    event_unsubscribe_if_flag_set(evt, last_handler);
    return 0;
}