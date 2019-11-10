
#include <stdio.h>
#include <stdlib.h>
#include "button.h"

//a debouncer instance (not necessary)
struct debouncer db;
struct debouncer db1;

//some button instances
struct button bt;
struct button combo;

//button event handler fun, takes pointer to button as ctx
void button_handler(enum button_event evt, void *ctx) {
    switch (evt) {
    case BUTTON_EVENT_PRESS:
        if (ctx == &bt)
            /*printf("button bt pressed\n"); */
            break;
        else
            /*printf("button combo pressed\n");*/
        break;
    case BUTTON_EVENT_RELEASE:
        if (ctx == &bt)
            /*printf("button bt released\n"); */
            break;
        else
            /*printf("button combo released\n");*/
        break;
    case BUTTON_EVENT_HOLD:
        if (ctx == &bt)
            printf("button bt held\n"); 
        else
            printf("button combo held\n");
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
    debouncer_init(&db, 3, false);
    debouncer_init(&db1, 3, false);
    
    //initialize buttons with initial state and handler function
    //buttons will always handle press and release events
    button_init(&bt, false, button_handler);
    button_init(&combo, false, button_handler);
    
    //to get hold and repeat events we have to ask for it
    button_set_hold_time(&combo, 50/*ms*/, true);
    button_set_repeat_time(&combo, 10, true);
    
    unsigned long long time = 0;
    while (time < 1000000) {
        //get the hardware button state
        bool hardware_button_state = rand() % 2;
        
        //apply debouncing
        hardware_button_state = debouncer_update(&db, hardware_button_state);
        
        //update simple button (pass pointer to button as context)
        button_update(&bt, time, hardware_button_state, &bt);
        
        //update combo button
        bool other_state = rand() % 2;
        other_state = debouncer_update(&db1, other_state);
        button_update(&combo, time, hardware_button_state && other_state, &combo);
        
        time++;
    }
}