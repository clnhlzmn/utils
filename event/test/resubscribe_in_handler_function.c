#include "event.h"
#include <assert.h>
#include <stdbool.h>
#include <stddef.h>

static struct event event;
static struct event event2;

static struct event_handler handler;

static int handled;

static void handler_cb(struct event *evt, void *ctx) {
    (void)ctx;
    handled++;
    if (evt == &event) {
        struct event_handler *current_handler = event_get_current_handler(evt);
        event_unsubscribe(evt, current_handler);
        assert(event_subscribe(&event2, current_handler) == 0 && "event_subscribe should return 0 from within a handler");
        assert(event_subscribe(&event2, current_handler) != 0 && "event_subscribe should not return 0 when handler is already subscribed");
    }
}

int main(void) {
    event_init(&event);
    event_init(&event2);
    event_handler_init(&handler, handler_cb);
    event_subscribe(&event, &handler);
    event_publish(&event, NULL);
    assert(handled == 1 && "event handler should have been called");
    event_publish(&event, NULL);
    assert(handled == 1 && "event handler should not have been called");
    event_publish(&event2, NULL);
    assert(handled == 2 && "event handler for event2 should have been called");
    return 0;
}
