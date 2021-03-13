#include "event.h"
#include <assert.h>
#include <stdbool.h>
#include <stddef.h>

#define CONTAINER_OF(ptr, type, member) \
    ( (type *) ((char *)ptr - offsetof(type,member)) )

static struct event event;

static int handled;

struct event_handler_container {
    struct event_handler handler;
    int data;
};

static struct event_handler_container container0;
static struct event_handler_container container1;

static void handler_cb(struct event *evt, void *ctx) {
    (void)ctx;
    struct event_handler *current_handler = event_get_current_handler(evt);
    struct event_handler_container *container = CONTAINER_OF(current_handler, struct event_handler_container, handler);
    handled |= 1 << container->data;
}

int main(void) {
    event_init(&event);
    
    event_handler_init(&container0.handler, handler_cb);
    event_handler_init(&container1.handler, handler_cb);
    container0.data = 0;
    container1.data = 1;
    
    event_subscribe(&event, &container0.handler);
    assert(event_subscribe(&event, &container1.handler) == 0 && "event_subscribe should return 0 when subscribing a second event");
    
    handled = 0;
    event_publish(&event, NULL);
    assert(handled == 3 && "all handler functions should be called when more than one is subscribed");
    
    return 0;
}
