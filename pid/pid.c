#include <float.h>
#include "pid.h"

enum pid_flags {
    PID_HAVE_LAST_ERROR = 1,
};

void pid_init(struct pid *self, const struct pid_gain *gains) {
    self->gain = gains;
    self->last_error = 0;
    self->integral = 0;
    self->max_integral = FLT_MAX;
    self->output = 0;
    self->flags = 0;
}

void pid_set_max_integral(struct pid *self, float value) {
    self->max_integral = value;
}

void pid_reset(struct pid *self) {
    self->integral = 0;
    self->flags &= ~PID_HAVE_LAST_ERROR;
}

float pid_update(struct pid *self, float error) {
    self->output = self->gain->p * error;
    if (self->gain->i) {
        self->integral += self->gain->i * error;
        if (self->integral > self->max_integral)
            self->integral = self->max_integral;
        else if (self->integral < -self->max_integral) {
            self->integral = -self->max_integral;
        }
        self->output += self->integral;
    }
    if (self->gain->d) {
        if (self->flags & PID_HAVE_LAST_ERROR) {
            self->output += self->gain->d * (error - self->last_error);
        } else {
            self->flags |= PID_HAVE_LAST_ERROR;
        }
        self->last_error = error;
    }
    return self->output;
}

float pid_get_output(const struct pid *self) {
    return self->output;
}
