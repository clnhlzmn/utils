#include "event.h"
#include <assert.h>
#include <stdbool.h>

static bool handled = false;

static void handler_cb(struct event *evt, void *ctx) {
    (void)evt; (void)ctx;
    handled = true;
}

int main(void) {
    struct event event;
    struct event_handler handler;
    
    assert(event_init(NULL) != 0 && "event_init should not return 0 when event is NULL");
    assert(event_init(&event) == 0 && "event_init should return 0");
    
    assert(event_handler_init(NULL, handler_cb) != 0 && "event_handler_init should not return 0 when handler is NULL");
    assert(event_handler_init(&handler, handler_cb) == 0 && "event_handler_init should return 0");
    
    assert(event_publish(NULL, NULL) != 0 && "event_publish should not return 0 when event is NULL");
    assert(event_publish(&event, NULL) == 0 && "event_publish should return 0");
    assert(handled == false && "handler function should not be called if handler wasn't subscribed");
    
    assert(event_subscribe(NULL, &handler) != 0 && "event_subscribe should not return 0 when event is NULL");
    assert(event_subscribe(&event, NULL) != 0 && "event_subscribe should not return 0 when handler is NULL");
    assert(event_subscribe(&event, &handler) == 0 && "event_subscribe should return 0");
    
    handled = false;
    event_publish(&event, NULL);
    assert(handled == true && "handler function should be called if handler was subscribed");
    
    assert(event_unsubscribe(NULL, &handler) != 0 && "event_unsubscribe should not return 0 when event is NULL");
    assert(event_unsubscribe(&event, NULL) != 0 && "event_unsubscribe should not return 0 when handler is NULL");
    assert(event_unsubscribe(&event, &handler) == 0 && "event_unsubscribe should return 0");
    
    handled = false;
    event_publish(&event, NULL);
    assert(handled == false && "handler function should not be called if handler was unsubscribed");
    
    return 0;
}
