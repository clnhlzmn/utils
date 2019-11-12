
#include "../pool.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

//create pool for 10 longs
POOL(test, long, 10);

//create an instance
struct pool_test my_pool;

int main(void) {
    //init instance
    assert(pool_test_init(&my_pool) == 0);
    
    //a place to store my allocations
    long *ints[10] = {0};
    
    //first make sure we can alloc 10
    for (int i = 0; i < 10; ++i) {
        ints[i] = pool_test_alloc(&my_pool);
        assert(ints[i]);
        *ints[i] = i;
    }
    
    //do a lot of allocs and frees
    for (int _ = 0; _ < 100000; ++_) {
        //pick an index
        int i = rand() % 10;
        //if it's allocated
        if (ints[i]) {
            //check the value
            assert(*ints[i] == i);
            //free it
            pool_test_free(&my_pool, ints[i]);
            //set to NULL so we know
            ints[i] = NULL;
        } else {
            //else allocate
            ints[i] = pool_test_alloc(&my_pool);
            //if successful set value
            if (ints[i])
                *ints[i] = i;
        }
    }
    printf("tests passed\r\n");
}
