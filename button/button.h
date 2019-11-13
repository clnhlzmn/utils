
/**
\file button.h
\brief Structures and functions for handling software debouncing, edge detection, and button press, release, hold, and repeat events.
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

static inline void debouncer_set_count(struct debouncer *self, int count);

/**
\brief initialize a debouncer
\param self pointer to instance
\param count how many times input state should repeat before output state changes
\param initial initial output state
*/
static inline void debouncer_init(
    struct debouncer *self, int count, bool initial) {
    self->current_value = initial;
    debouncer_set_count(self, count);
}

/**
set the count for a debouncer
*/
static inline void debouncer_set_count(struct debouncer *self, int count) {
    if (count < 1) {
        count = 1;
    }
    self->reset_count = count;
    self->current_count = self->reset_count;
}

/**
update debouncer state
value is input state
returns output state after debouncing
*/
static inline bool debouncer_update(struct debouncer *self, bool value) {
    if (self->current_value != value) {
        if (--self->current_count == 0) {
            self->current_count = self->reset_count;
            self->current_value = value;
        }
    } else {
        self->current_count = self->reset_count;
    }
    return self->current_value;
}

/**
get the output state of the debouncer
*/
static inline bool debouncer_value(struct debouncer *self) {
    return self->current_value;
}

/**
return values for edge_detector_update
*/
enum edge_detector_edge {
    EDGE_NONE,
    EDGE_RISING,
    EDGE_FALLING,
};

/**
edge detector state
*/
struct edge_detector {
    bool value;
};

/**
initialize an edge detector
initial is initial state
*/
static inline void edge_detector_init(struct edge_detector *self, 
    bool initial) {
    self->value = initial;
}

/**
input new state to edge detector
value is new state
return value is type of edge detected (none, rising, falling)
*/
static inline enum edge_detector_edge 
    edge_detector_update(struct edge_detector *self, 
                         bool value) {
    if (value != self->value) {
        self->value = value;
        if (value) {
            return EDGE_RISING;
        } else {
            return EDGE_FALLING;
        }
    }
    return EDGE_NONE;
}

/**
get the current value of an edge detector
*/
static inline bool edge_detector_get_value(struct edge_detector *self) {
    return self->value;
}

/**
button events
*/
enum button_event {
    BUTTON_EVENT_PRESS,
    BUTTON_EVENT_RELEASE,
    BUTTON_EVENT_HOLD
};

/**
internal button timer state
*/
enum button_timer_state {
    BUTTON_TIMER_IDLE,
    BUTTON_TIMER_HOLD,
    BUTTON_TIMER_REPEAT
};

/**
button state
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
static inline void button_init(struct button *self, bool initial, 
    void (*handler)(enum button_event, void *)) {
    edge_detector_init(&self->edge_detector, initial);
    self->handler = handler;
    self->use_hold_timer = false;
    self->use_repeat_timer = false;
    self->timer_state = BUTTON_TIMER_IDLE;
    self->time = 0;
    self->hold_time = 0;
    self->repeat_time = 0;
}

/**
set the button hold time
time is hold delay time
use indicates if hold events should be generated
*/
static inline void button_set_hold_time(struct button *self, 
    unsigned long long time, bool use) {
    self->hold_time = time;
    self->use_hold_timer = use;
}

/**
set the button repeat time
time is repeat delay time
use indicates if repeat events should be generated
*/
static inline void button_set_repeat_time(struct button *self, 
    unsigned long long time, bool use) {
    self->repeat_time = time;
    self->use_repeat_timer = use;
}

/**
get the current button value (false=not pressed, true=pressed)
*/
static inline bool button_get_value(struct button *self) {
    return edge_detector_get_value(&self->edge_detector);
}

/**
input new state to a button
time is current time
value is current button state (read from hardware or any other source)
ctx is pointer to ctx that will be passed to handler function on event
*/
static inline bool button_update(struct button *self, 
                                 unsigned long long time, 
                                 bool value,
                                 void *ctx) {
    enum edge_detector_edge edge = 
        edge_detector_update(&self->edge_detector, value);
    switch (edge) {
        case EDGE_NONE: //nothing
            break;
        case EDGE_RISING:
            if (self->use_hold_timer) {
                self->time = time;
                self->timer_state = BUTTON_TIMER_HOLD;
            }
            if (self->handler)
                self->handler(BUTTON_EVENT_PRESS, ctx);
            break;
        case EDGE_FALLING:
            self->timer_state = BUTTON_TIMER_IDLE;
            if (self->handler)
                self->handler(BUTTON_EVENT_RELEASE, ctx);
            break;
    }
    if ((self->timer_state == BUTTON_TIMER_HOLD 
            && time - self->time >= self->hold_time) ||
        (self->timer_state == BUTTON_TIMER_REPEAT 
            && time - self->time >= self->repeat_time)) {
        if (self->use_repeat_timer) {
            self->time = time;
            self->timer_state = BUTTON_TIMER_REPEAT;
        } else {
            self->timer_state = BUTTON_TIMER_IDLE;
        }
        if (self->handler)
            self->handler(BUTTON_EVENT_HOLD, ctx);
    }
    return button_get_value(self);
}

#endif //BUTTON_UTILS_H

