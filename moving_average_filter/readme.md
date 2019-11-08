# A simple generic efficient moving average filter for microcontrollers

Useful for filtering analog inputs to produce a smooth looking output for display.

## features

* simple
* generic
* efficient
   * inputting values to the filter takes constant time regardless of the filter size
   * if filter size is a power of 2 then division operations (slow) will likely be removed by the compiler

* no dynamic memory allocation

## example

    #include <stdio.h>
    #include "moving_average_filter.h"

    //create maf_example to filter 5 samples of analog value
    MOVING_AVERAGE_FILTER(example, int, 5);

    //create instance
    struct maf_example filt;

    int main(void) {
        //init filter
        maf_example_init(&filt);
        while (1) {
            //get raw analog value
            int val = read_analog_pin();
            //filter the value
            int filtered = maf_example_input(&filt, val);
            //show filtered value
            printf("filtered value %d", filtered);
        }
    }

