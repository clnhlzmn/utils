#include <float.h>
#include "pid.h"

enum pid_flags {
    PID_USE_D = 1,
    PID_USE_I = 2,
    PID_HAVE_LAST_ERROR = 4,
};

void pid_init(struct pid *self, const struct pid_gain *gains) {
    self->gain = gain;
    self->last_error = 0;
    self->integral = 0;
    self->max_integral = FLT_MAX;
    self->output = 0;
    self->flags = PID_USE_D | PID_USE_I;
}

void pid_set_max_integral(struct pid *self, float value) {
    self->max_integral = value;
}

void pid_use_d(struct pid *self, bool value) {
    if (value) self->flags |= PID_USE_D;
    else self->flags &= ~PID_USE_D;
}

void pid_use_i(struct pid *self, bool value) {
    if (value) self->flags |= PID_USE_I;
    else self->flags &= ~PID_USE_I;
}

void pid_reset(struct pid *self, float value) {
    self->integral = 0;
    self->flags &= ~PID_HAVE_LAST_ERROR;
}

float pid_update(struct pid *self, float error) {
    self->output = self->gain->p * error;
    if (self->flags & PID_USE_D && self->flags & PID_HAVE_LAST_ERROR) {
        if (self->flags & PID_HAVE_LAST_ERROR) {
            self->output += self->gain->d * (error - self->last_error);
        } else {
            self->flags |= PID_HAVE_LAST_ERROR;
        }
        self->last_error = error;
    }
    if (self->flags & PID_USE_I) {
        self->integral += self->gain->i * error;
        if (self->integral > self->max_integral)
            self->integral = self->max_integral;
        else if (self->integral < -self->max_integral) {
            self->integral = -self->max_integral;
        }
        self->output += self->integral;
    }
    return self->output;
}

float pid_get_output(struct pid *self) {
    return self->output;
}
