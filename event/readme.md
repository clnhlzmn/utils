# event

A single header library that implements the publish/subscribe pattern.

# example

```c

#include <stdio.h>
#include "event.h"

struct event my_event;

struct event_handler my_handler;

void my_handler_fun(struct event *evt, void *ctx) {
    printf("handled event\r\n");
}

int main(void) {
    
    //initialize event
    event_init(&my_event);
    
    //initialize zero or more event handers
    event_handler_init(&my_handler, my_handler_fun);
    
    //and subscribe them to events
    event_subscribe(&my_event, &my_handler);
    
    //publish event and all subscribed handlers will be invoked
    event_publish(&my_event, NULL);
    return 0;
}
```