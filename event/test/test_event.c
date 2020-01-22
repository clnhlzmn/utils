
#include <stdio.h>
#include <assert.h>

#include "../event.h"

struct event event1;
struct event event2;

struct event_handler handler1;
struct event_handler handler2;
struct event_handler handler_unsubscribe;

struct event *current_event;
struct event_handler *current_handler;

void handler_fun(struct event *evt, void *ctx) {
    assert(evt == current_event);
    assert(ctx == current_handler);
}

void handler_fun_unsubscribe(struct event *evt, void *ctx) {
    assert(evt == current_event);
    assert(ctx == current_handler);
    event_unsubscribe(evt, (struct event_handler*)ctx);
}

int main(void) {
    //init events and handlers
    assert(event_init(&event1) == 0);
    assert(event_init(&event2) == 0);
    assert(event_handler_init(&handler1, handler_fun) == 0);
    assert(event_handler_init(&handler2, handler_fun) == 0);
    //sub handler1 to event1
    assert(event_subscribe(&event1, &handler1) == 0);
    assert(event_subscribe(&event1, &handler1) != 0);
    
    //check that handler1 is called on event1
    current_handler = &handler1;
    current_event = &event1;
    assert(event_publish(&event1, &handler1) == 0);
    //and not on event2
    assert(event_publish(&event2, &handler1) == 0);
    
    //check that unsubscribing handler2 from event1 doesn't work (not subscribed)
    assert(event_unsubscribe(&event1, &handler2) != 0);
    //but that unsubscribing handler1 from event1 does work
    assert(event_unsubscribe(&event1, &handler1) == 0);
    current_handler = NULL;
    //handler1 shouldn't be called
    assert(event_publish(&event1, &handler1) == 0);
    //handler 2 shouldn't be called
    current_event = &event2;
    assert(event_publish(&event2, &handler2) == 0);
    
    //reinit handler1 with unsub function
    assert(event_handler_init(&handler1, handler_fun_unsubscribe) == 0);
    //sub handler1 to event1
    assert(event_subscribe(&event1, &handler1) == 0);
    current_event = &event1;
    current_handler = &handler1;
    //check that handler1 is called
    assert(event_publish(&event1, &handler1) == 0);
    //check that handler1 is already unsubscribed
    assert(event_subscribe(&event1, &handler1) == 0);
    printf("tests passed\r\n");
    return 0;
}
