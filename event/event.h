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

/*
event state
*/
struct event {
    struct list handlers;
};

/*
event handler state
*/
struct event_handler {
    struct list_element element;
    void (*fun)(struct event *evt, void *ctx);
};

/*
initialize an event handler
fun is a function to be called when the subscribed event is published
*/
static inline int event_handler_init(struct event_handler *handler, void (*fun)(struct event *, void *)) {
    if (!handler) return -1;
    list_element_init(&handler->element);
    handler->fun = fun;
    return 0;
}

/*
initialize an event
*/
static inline int event_init(struct event *evt) {
    if (!evt) return -1;
    list_init(&evt->handlers);
    return 0;
}

/*
attach an event handler to an event
*/
static inline int event_subscribe(struct event *evt, struct event_handler *handler) {
    if (!evt || !handler) return -1;
    return list_append(&evt->handlers, &handler->element);
}

/*
detach an event handler from an event
*/
static inline int event_unsubscribe(struct event *evt, struct event_handler *handler) {
    if (!evt || !handler) return -1;
    return list_remove(&evt->handlers, &handler->element);
}

/*
publish an event
ctx will be passed to the handler functions of subscribed handlers
*/
static inline int event_publish(struct event *evt, void *ctx) {
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
