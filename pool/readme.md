# pool

A single header generic pool allocator.

## how to use

1. Include `pool.h` (`pool.h` requires `slist.h` so make sure your compiler can find that too).
2. Create an instance of the pool types and functions by passing a name, type, and size to the macro `POOL` like `POOL(my_pool, int, 100)`.
3. Create one or more instances of the pool type you created like `struct pool_my_pool my_pool_instance;`. Each instance is capable of allocating up to 100 (the size you pass to `POOL`) objects of the type you specified.
4. Allocate and free objects with `int *obj = pool_my_pool_alloc(&my_pool_instance);` and `pool_my_pool_free(&my_pool_instance, obj);`.

## example

See `test/test_pool.c`.