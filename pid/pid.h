#ifndef PID_H
#define PID_H

#include <stdint.h>
#include <stdbool.h>

struct pid_gain {
    float p;
    float i;
    float d; 
};

struct pid {
    const struct pid_gain *gain;
    float last_error;
    float integral;
    float max_integral;
    float output;
    uint8_t flags;
};

void pid_init(struct pid *, const struct pid_gain *);

void pid_set_max_integral(struct pid *, float);

void pid_reset(struct pid *);

float pid_update(struct pid *, float error);

float pid_get_output(const struct pid *);

#endif /*PID_H*/
