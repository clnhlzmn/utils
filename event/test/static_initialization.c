#include <assert.h>
#include <string.h>
#include "event.h"

static struct event event = EVENT_INIT(event);

static int handled;

static void handler_cb(struct event *, void *);

static struct event_handler handler = EVENT_HANDLER_INIT(handler_cb);

static void handler_cb(struct event *evt, void *ctx) {
    (void)ctx;
    handled++;
    assert(&handler == event_get_current_handler(evt) && "current handler should be correct");
}

int main(void) {
    assert(event_subscribe(&event, &handler) == 0 && "event_subscribe should return 0");
    assert(event_publish(&event, NULL) == 0 && "event_publish should return 0");
    assert(handled == 1 && "the handler function should have been called");
    assert(event_unsubscribe(&event, &handler) == 0 && "event_unsubscribe should return 0");
    event_publish(&event, NULL);
    assert(handled == 1 && "the handler function should not have been called");
    return 0;
}
