# button

A single header library for handling software debouncing, edge dectection, and button press/release/hold/repeat events.

## example

#include "button.h"

```c
//a debouncer instance (not necessary)
struct debouncer db;

//some button instances
struct button bt;
struct button combo;

//button event handler fun, takes pointer to button as ctx
void button_handler(enum button_event evt, void *ctx) {
    switch (evt) {
    case BUTTON_EVENT_PRESSED:
        if (ctx == &bt) {}//bt button pressed
        else {}//combo button pressed
        break;
    case BUTTON_EVENT_RELEASED:
        if (ctx == &bt) {}//bt button released
        else {}//combo button released
        break;
    case BUTTON_EVENT_HELD:
        if (ctx == &bt) {}//bt button held
        else {}//combo button held
        break;
    }
}

//a function to get the physical hardware button state (true is pressed)
bool get_hw_button_state(void);

//a function to get other state to be used in combination with hardware button state
//for struct button combo. This could be another hardware button or any other state.
bool get_other_state(void);

//a function to get the current system time (in ms)
unsigned long get_time_ms(void);

int main(void) {
    
    //initialize debouncer with number of counts and initial state
    debouncer_init(&db, 5, false);
    
    //initialize buttons with initial state and handler function
    //buttons will always handle press and release events
    button_init(&bt, false, button_handler);
    button_init(&combo, false, button_handler);
    
    //to get hold and repeat events we have to ask for it
    button_set_hold_time(&combo, 500/*ms*/, true);
    button_set_repeat_time(&combo, 100, true);
    
    while (true) {
        //get the hardware button state
        bool hardware_button_state = get_hw_button_state();
        
        //apply debouncing
        hardware_button_state = debouncer_update(&db, hardware_button_state);
        
        //update simple button (pass pointer to button as context)
        button_update(&bt, get_time_ms(), hardware_button_state, &bt);
        
        //update combo button
        bool other_state = get_other_state();
        button_update(&combo, get_time_ms(), hardware_button_state && other_state, &combo);
    }
}
```