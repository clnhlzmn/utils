

#include <stdio.h>
#include <assert.h>
#include "queue.h"

#define COUNT (100)
QUEUE(test, int, COUNT)

int cb(volatile int *item, volatile void *ctx) {
    assert(*item == *(int*)ctx  && "queue_*_foreach items not equal");
    (*(int*)ctx)++;
    return 0;
}

int main() {
    //create instance
    struct queue_test q;
    //initialize
    queue_test_init(&q);
    assert(queue_test_count(&q) == 0);
    //a value
    int val = -1;
    assert(queue_test_pop(&q, &val) != 0 && "queue_*_pop should not return zero when queue is empty");
    //check that we can insert COUNT items
    for (int i = 0; i < COUNT; ++i) {
        assert(queue_test_push(&q, &i) == 0 && "queue_*_push should return zero when queue is not full");
    }
    //
    assert(queue_test_count(&q) == COUNT);
    //check foreach
    int test = 0;
    queue_test_foreach(&q, cb, &test);
    //check that we can't push any more
    assert(queue_test_push(&q, &val) != 0 && "queue_*_push should not return zero when queue is full");
    //check that we can remove the same COUNT items
    for (int i = 0; i < COUNT; ++i) {
        val = -1;
        assert(queue_test_pop(&q, &val) == 0 && "queue_*_pop should return zero when queue is not empty");
        assert(val == i && "queue_*_pop popped incorrect value");
    }
    //check that we can't pop any more
    assert(queue_test_pop(&q, &val) != 0 && "queue_*_pop should not return zero when queue is empty");
    printf("tests passed\r\n");
    return 0;
}
