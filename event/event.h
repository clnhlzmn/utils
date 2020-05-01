/**
\file event.h
\brief an implementation of the publish/subscribe pattern
\details depends on \ref list.h
 */ 

#ifndef EVENT_H_
#define EVENT_H_

#include "list.h"

/**
\brief event state
*/
struct event {
    /** \brief a list of event handlers that are subscribed to this event*/
    struct list handlers;
};

/**
\brief event handler state
*/
struct event_handler {
    /** \brief list element for attaching handler to an event */
    struct list_element element;
    /** \brief handler function pointer 
    \param evt a pointer to the \c struct \c event being published
    \param ctx a pointer to the context that was passed to \c event_publish
    */
    void (*fun)(struct event *evt, void *ctx);
    /** \brief pointer to keep track of which event to subscribe to 
    once handler finishes */
    struct event *evt;
    /** \brief flag used to indicate if the handler should be removed */
    unsigned char flags;
};

/**
\brief allows static initialization of an \ref event_handler
\details
~~~~~~~~~~~~~~~{.c}
struct event_handler my_handler = EVENT_HANDLER_INIT(my_handler_fun);
~~~~~~~~~~~~~~~
*/
#define EVENT_HANDLER_INIT(handler_fun) {            \
    .element = (struct list_element){ NULL, NULL },  \
    .fun = handler_fun,                              \
    .evt = NULL,                                     \
    .flags = 0                                       \
}

/**
\brief initialize an event handler
\param handler pointer to \ref event_handler
\param fun a function to be called when the subscribed event is published
*/
int event_handler_init(struct event_handler *handler, void (*fun)(struct event *, void *));

/**
\brief initialize a \ref event
\param evt pointer to \ref event
\return 0 if successful
*/
int event_init(struct event *evt);

/**
\brief allows static initialization of an \ref event
\details
~~~~~~~~~~~~~~~{.c}
struct event my_event = EVENT_INIT(my_event);
~~~~~~~~~~~~~~~
*/
#define EVENT_INIT(event) { .handlers = LIST_INIT((event).handlers) }

/**
\brief attach an \ref event_handler to an \ref event
\note if one subscribes to an event from within 
a handler for that event the newly subscribed handler
won't be called until the next time that event is published
\param evt pointer to initialized \ref event
\param handler pointer to initialized \ref event_handler
\return 0 if successful
*/
int event_subscribe(struct event *evt, struct event_handler *handler);

/**
\brief detach an \ref event_handler from an \ref event
\note unsubscribing a handler from within that handler's
callback function is undefined
\param evt pointer to initialized \ref event
\param handler pointer to initialized \ref event_handler
\return 0 if the handler was unsubscribed
*/
int event_unsubscribe(struct event *evt, struct event_handler *handler);

/**
\brief publish an \ref event
\details all subscribed events will have their handler functions called in an unspecified order
\sa \ref event_handler_init and \ref event_subscribe
\param evt pointer to initialized \ref event
\param ctx pointer to context to pass to subscribed \ref event_handler functions
\return 0 if successful
*/
int event_publish(struct event *evt, void *ctx);

#endif /* EVENT_H_ */
