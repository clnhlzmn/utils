# A simple generic FIFO queue in C for microcontrollers

Originally based on [Microcontrollers: Interrupt-safe ring buffers]. However, I have since modified the code such that it is not safe for interrupts, but it is more portable without any assumptions.

## features

* works with elements of any type
* overhead of `3 * sizeof(size_t)`
* no dynamic allocation
* simple api `init`, `push`, `pop`

## how to use

1. Include `queue.h`.
2. Create an instance of the queue type and functions by passing a name, type, and size to the macro `QUEUE`.
3. Create an instance of the type, `struct queue_*` where `*` is the name you passed to `QUEUE`.
4. Initialize the instance with `queue_*_init`. 
5. Push and pop with `queue_*_push` and `queue_*_pop`.

## example

```c
#include "queue.h"

//define a queue called queue_example 
//with elements of type int and size 8
QUEUE(example, int, 8);

//create an instance of queue_example
volatile struct queue_example queue;

//analog to digital converter isr
void adc_isr(void) {
    int value = get_adc_value();
    if (queue_push(&queue, &value) == 0) {
        //push successful, no action required
    } else {
        //not enough room in queue, handle appropriately here
    }
}

int main(void) {
    //initialize the instance
    queue_example_init(&queue);
    while (1) {
        ATOMIC_BLOCK(ATOMIC_RESTORESTATE) { //atomic section for atmel avr
            int value;
            if (queue_example_pop(&queue, &value) == 0) {
                //one element removed and stored in value
                printf("%d\r\n", value);
            } else {
                //queue empty
                continue;
            }
        }
    }
}
```
    
[Microcontrollers: Interrupt-safe ring buffers]: https://www.downtowndougbrown.com/2013/01/microcontrollers-interrupt-safe-ring-buffers/