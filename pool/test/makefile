test: ../pool.h test_pool.c out
	gcc test_pool.c -I ../../list -g -o out/test -Wall -Wextra -Werror -std=c99
	./out/test

out:
	mkdir out

.PHONY: clean
clean:
	rm -rf out