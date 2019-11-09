
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include "../button.h"

#define N (10)

enum output_event {
    NONE,
    PRESSED,
    RELEASED,
    HELD
};

void test_debouncer(struct debouncer *db, bool *input, bool *expected_output) {
    bool actual_output_state[N];
    for (int i = 0; i < N; ++i) {
        actual_output_state[i] = debouncer_update(db, input[i]);
    }
    for (int i = 0; i < N; ++i) {
        assert(actual_output_state[i] == expected_output[i]);
    }
}

struct button_test_context {
    int *output;
    int index;
};

void button_test_event_handler(enum button_event evt, void *ctx) {
    struct button_test_context *context = ctx;
    context->output[context->index] = evt + 1;
}

void test_button(struct button *button, bool *input_state, int *expected_output_state) {
    unsigned long time = 0;
    int actual_output_state[N] = {0};
    struct button_test_context ctx = {actual_output_state, 0};
    for (int i = 0; i < N; ++i) {
        ctx.index = i;
        button_update(button, time, input_state[i], &ctx);
        time++;
    }
    for (int i = 0; i < N; ++i) {
        if (actual_output_state[i] != expected_output_state[i]) {
            assert(false);
        }
    }
}

int main(void) {
    {
        bool input_state[N] = {false, true, false, true, false, true, false, true, false, true};
        bool expected_output_state[N] = {false, true, false, true, false, true, false, true, false, true};
        struct debouncer db;
        debouncer_init(&db, 1, false);
        test_debouncer(&db, input_state, expected_output_state);
    }
    {
        bool input_state[10] = {false, true, false, true, false, true, false, true, false, true};
        bool expected_output_state[10] = {false, false, false, false, false, false, false, false, false, false};
        struct debouncer db;
        debouncer_init(&db, 2, false);
        test_debouncer(&db, input_state, expected_output_state);
    }
    {
        bool input_state[10] = {false, true, true, true, false, true, false, false, true, true};
        bool expected_output_state[10] = {false, false, true, true, true, true, true, false, false, true};
        struct debouncer db;
        debouncer_init(&db, 2, false);
        test_debouncer(&db, input_state, expected_output_state);
    }
    {
        bool input_state[N] = {false, false, false, false, false, true, true, true, true, true};
        int expected_output_state[N] = {NONE, NONE, NONE, NONE, NONE, PRESSED, NONE, NONE, NONE, NONE};
        struct button button;
        button_init(&button, false, button_test_event_handler);
        test_button(&button, input_state, expected_output_state);
    }
    {
        bool input_state[N] = {false, false, false, false, false, true, true, true, true, true};
        int expected_output_state[N] = {NONE, NONE, NONE, NONE, NONE, PRESSED, HELD, NONE, NONE, NONE };
        struct button button;
        button_init(&button, false, button_test_event_handler);
        button_set_hold_time(&button, 1, true);
        test_button(&button, input_state, expected_output_state);
    }
    {
        bool input_state[N] = {false, false, false, false, false, true, true, true, true, true};
        int expected_output_state[N] = {NONE, NONE, NONE, NONE, NONE, PRESSED, HELD, HELD, HELD, HELD};
        struct button button;
        button_init(&button, false, button_test_event_handler);
        button_set_hold_time(&button, 1, true);
        button_set_repeat_time(&button, 1, true);
        test_button(&button, input_state, expected_output_state);
    }
    {
        bool input_state[N] = {false, false, true, true, false, false, true, true, false, false};
        int expected_output_state[N] = {NONE, NONE, PRESSED, NONE, RELEASED, NONE, PRESSED, NONE, RELEASED, NONE};
        struct button button;
        button_init(&button, false, button_test_event_handler);
        test_button(&button, input_state, expected_output_state);
    }
    printf("tests passed\r\n");
    return 0;
}