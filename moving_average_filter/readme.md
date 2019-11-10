# A simple generic efficient moving average filter for microcontrollers

Useful for filtering analog inputs to produce a smooth looking output for display.

## features

* simple
* generic
* efficient
   * inputting values to the filter takes constant time regardless of the filter size
   * if filter size is a power of 2 then division operations (slow) will likely be removed by the compiler

* no dynamic memory allocation

## how to use

1. Include `moving_average_filter.h`
2. Create an instance of the moving average filter type with a name, type, and size with the macro `MOVING_AVERAGE_FILTER`.
3. Create an instance of `struct maf_*` where `*` is the name you passed to `MOVING_AVERAGE_FILTER`.
4. Initialize the instance with `maf_*_init` and input new values with `maf_*_input`.

## example

```c
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
```