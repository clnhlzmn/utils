#include "../pool.h"
#include <stdio.h>
#include <assert.h>

POOL(test, long, 10);

struct pool_test my_pool;

int main(void) {
    assert(pool_test_init(&my_pool) == 0);
    printf("tests passed\r\n");
}
