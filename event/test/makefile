test: ../../list/list.h ../../list/list.c test_event.c ../event.c ../event.h out
	gcc -o out/test -Wall -Wextra -Werror -I../../list/ -g test_event.c ../event.c ../../list/list.c
	./out/test

out:
	mkdir out

clean:
	rm -rf out