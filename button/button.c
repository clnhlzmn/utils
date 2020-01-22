#include "button.h"

void debouncer_init(
    struct debouncer *self, int count, bool initial) {
    self->current_value = initial;
    debouncer_set_count(self, count);
}

void debouncer_set_count(struct debouncer *self, int count) {
    if (count < 1) {
        count = 1;
    }
    self->reset_count = count;
    self->current_count = self->reset_count;
}

bool debouncer_update(struct debouncer *self, bool value) {
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

bool debouncer_value(struct debouncer *self) {
    return self->current_value;
}

void edge_detector_init(struct edge_detector *self, 
    bool initial) {
    self->value = initial;
}

enum edge_detector_edge 
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

bool edge_detector_get_value(struct edge_detector *self) {
    return self->value;
}

void button_init(struct button *self, bool initial, 
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

void button_set_hold_time(struct button *self, 
    unsigned long long time, bool use) {
    self->hold_time = time;
    self->use_hold_timer = use;
}

void button_set_repeat_time(struct button *self, 
    unsigned long long time, bool use) {
    self->repeat_time = time;
    self->use_repeat_timer = use;
}

bool button_get_value(struct button *self) {
    return edge_detector_get_value(&self->edge_detector);
}

bool button_update(struct button *self, 
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