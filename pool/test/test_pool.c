
#include "../pool.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

POOL(test, long, 10);

struct pool_test my_pool;

int main(void) {
    assert(pool_test_init(&my_pool) == 0);;
    long *ints[10] = {0};
    for (int _ = 0; _ < 100000; ++_) {
        int i = rand() % 10;
        if (ints[i]) {
            assert(*ints[i] == i);
            pool_test_free(&my_pool, ints[i]);
            ints[i] = NULL;
        } else {
            ints[i] = pool_test_alloc(&my_pool);
            if (ints[i])
                *ints[i] = i;
        }
    }
    printf("tests passed\r\n");
}
