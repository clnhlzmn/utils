
/**
\file button.h
\brief Structures and functions for handling software debouncing, 
edge detection, and button press, release, hold, and repeat events.
*/

#ifndef BUTTON_UTILS_H
#define BUTTON_UTILS_H

#include <stdbool.h>

/**
\brief a software debouncer
*/
struct debouncer {
    bool current_value;
    int reset_count;
    int current_count;
};

#define DEBOUNCER_INIT(initial, count) \
    {.current_value = initial, .reset_count = count, .current_count = count}

/**
\brief initialize a debouncer
\param self pointer to instance
\param count how many times input state should repeat before output state changes
\param initial initial output state
*/
void debouncer_init(
    struct debouncer *self, int count, bool initial);

/**
set the count for a debouncer
*/
void debouncer_set_count(struct debouncer *self, int count);

/**
update debouncer state
value is input state
returns output state after debouncing
*/
bool debouncer_update(struct debouncer *self, bool value);

/**
get the output state of the debouncer
*/
bool debouncer_value(struct debouncer *self);

/**
return values for edge_detector_update
*/
enum edge_detector_edge {
    EDGE_NONE,
    EDGE_RISING,
    EDGE_FALLING,
};

/**
\brief edge detector state
*/
struct edge_detector {
    bool value;
};

/**
initialize an edge detector
initial is initial state
*/
void edge_detector_init(struct edge_detector *self, 
    bool initial);

/**
input new state to edge detector
value is new state
return value is type of edge detected (none, rising, falling)
*/
enum edge_detector_edge 
    edge_detector_update(struct edge_detector *self, 
                         bool value);

/**
get the current value of an edge detector
*/
bool edge_detector_get_value(struct edge_detector *self);

/**
\brief button events
*/
enum button_event {
    BUTTON_EVENT_PRESS,
    BUTTON_EVENT_RELEASE,
    BUTTON_EVENT_HOLD
};

/**
\brief internal button timer state
*/
enum button_timer_state {
    BUTTON_TIMER_IDLE,
    BUTTON_TIMER_HOLD,
    BUTTON_TIMER_REPEAT
};

/**
\brief button state
*/
struct button {
    struct edge_detector edge_detector;
    void (*handler)(enum button_event, void *);
    bool use_hold_timer;
    bool use_repeat_timer;
    enum button_timer_state timer_state;
    unsigned long long time;
    unsigned long long hold_time;
    unsigned long long repeat_time;
};

/**
initialize a button
initial is initial state (false=not pressed, true=pressed)
handler is button event handler function
*/
void button_init(struct button *self, bool initial, 
    void (*handler)(enum button_event, void *));

/**
set the button hold time
time is hold delay time
use indicates if hold events should be generated
*/
void button_set_hold_time(struct button *self, 
    unsigned long long time, bool use);
/**
set the button repeat time
time is repeat delay time
use indicates if repeat events should be generated
*/
void button_set_repeat_time(struct button *self, 
    unsigned long long time, bool use);

/**
get the current button value (false=not pressed, true=pressed)
*/
bool button_get_value(struct button *self);

/**
input new state to a button
time is current time
value is current button state (read from hardware or any other source)
ctx is pointer to ctx that will be passed to handler function on event
*/
bool button_update(struct button *self, 
                   unsigned long long time, 
                   bool value,
                   void *ctx);

#endif //BUTTON_UTILS_H

