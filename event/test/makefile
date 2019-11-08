test: list.h test_event.c ../event.h
	gcc -o test -Wall -Wextra -Werror -I. test_event.c

list.h:
	curl https://api.github.com/repos/clnhlzmn/list/contents/list.h -H "Accept: application/vnd.github.v3.raw" >> list.h | bash

clean:
	rm -f list.h
	rm -rf test.exe
	rm -rf test