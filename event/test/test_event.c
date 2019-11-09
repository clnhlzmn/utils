
#include <stdio.h>
#include <assert.h>

#include "../event.h"

struct event event1;
struct event event2;

struct event_handler handler1;
struct event_handler handler2;

struct event *current_event;
struct event_handler *current_handler;

void handler_fun(struct event *evt, void *ctx) {
    assert(evt == current_event);
    assert(ctx == current_handler);
}

int main(void) {
    assert(event_init(&event1) == 0);
    assert(event_init(&event2) == 0);
    assert(event_handler_init(&handler1, handler_fun) == 0);
    assert(event_handler_init(&handler2, handler_fun) == 0);
    assert(event_subscribe(&event1, &handler1) == 0);
    assert(event_subscribe(&event1, &handler1) != 0);
    current_handler = &handler1;
    current_event = &event1;
    assert(event_dispatch(&event1, &handler1) == 0);
    assert(event_dispatch(&event2, &handler1) == 0);
    assert(event_unsubscribe(&event1, &handler2) != 0);
    assert(event_unsubscribe(&event1, &handler1) == 0);
    current_handler = NULL;
    assert(event_dispatch(&event1, &handler1) == 0);
    current_event = &event2;
    assert(event_dispatch(&event2, &handler2) == 0);
    printf("tests passed\r\n");
    return 0;
}
