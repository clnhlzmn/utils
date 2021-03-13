#include "event.h"
#include <assert.h>
#include <stdbool.h>
#include <stddef.h>

static struct event event;

static struct event_handler handler;

static int handled;

static void handler_cb(struct event *evt, void *ctx) {
    (void)ctx;
    handled++;
    struct event_handler *current_handler = event_get_current_handler(evt);
    assert(event_unsubscribe(evt, current_handler) == 0 && "event_unsubscribe should return 0 from within a handler function");
    assert(event_unsubscribe(evt, current_handler) != 0 && "event_unsubscribe should not return 0 when the handler is not subscribed");
}

int main(void) {
    event_init(&event);
    event_handler_init(&handler, handler_cb);
    event_subscribe(&event, &handler);
    handled = 0;
    event_publish(&event, NULL);
    assert(handled == 1 && "event handler should have been called");
    event_publish(&event, NULL);
    assert(handled == 1 && "event handler should not have been called");
    return 0;
}
