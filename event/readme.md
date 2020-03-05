# event

A library that implements the publish/subscribe pattern.

## how to use

1. Include `event.h/c` (`event.h/c` requires `list.h/c` so make sure your compiler can find those too).
2. Create instances of `struct event` for each event and initialize them with `event_init`.
3. Create instances of `struct event_handler`, and corresponding handler functions, for each event handler and initialize them with `event_handler_init`.
4. Subscribe handlers to events that they're interested in with `event_subscribe`.
5. Publish events with `event_publish`. The subscribed handler functions will be called.

## example

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
    
    //initialize zero or more event handlers
    event_handler_init(&my_handler, my_handler_fun);
    
    //and subscribe them to events
    event_subscribe(&my_event, &my_handler);
    
    //publish event and all subscribed handlers will be invoked
    event_publish(&my_event, NULL);
    return 0;
}
```
