#include "event.h"

enum {
    ACTIVE = 1,
};

int event_handler_init(struct event_handler *handler, void (*fun)(struct event *, void *)) {
    if (!handler) return -1;
    list_element_init(&handler->element);
    handler->fun = fun;
    handler->evt = NULL;
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
    if (handler->flags & ACTIVE && handler->evt) { //already subscribed
        return -1;
    } else if (handler->flags & ACTIVE && !handler->evt) { //not subscribed
        handler->evt = evt;
        return 0;
    } else {
        int err = list_prepend(&evt->handlers, &handler->element);
        if (!err) handler->evt = evt;
        return err;
    }
}

int event_unsubscribe(struct event *evt, struct event_handler *handler) {
    if (!evt || !handler) return -1;
    if (handler->flags & ACTIVE && handler->evt) { //subscribed
        handler->evt = NULL;
        return 0;
    } else if (handler->flags & ACTIVE && !handler->evt) { //not subscribed
        return -1;
    } else {
        int err = list_remove(&evt->handlers, &handler->element);
        if (!err) handler->evt = NULL;
        return err;
    }
}

static void event_update_subscription(struct event *evt, struct event_handler *handler) {
    if (!handler) return;
    if (!handler->evt) {
        event_unsubscribe(evt, handler);
    } if (handler->evt && handler->evt != evt) {
        struct event* new_evt = handler->evt;
        event_unsubscribe(evt, handler);
        event_subscribe(new_evt, handler);
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
        event_update_subscription(evt, last_handler);
        last_handler = handler;
    }
    event_update_subscription(evt, last_handler);
    return 0;
}