test: ../list.h test_list.c ../slist.h test_slist.c out
	gcc test_list.c -g -o out/list -Wall -Wextra -Werror -std=c99
	./out/list
	gcc test_slist.c -g -o out/slist -Wall -Wextra -Werror -std=c99
	./out/slist

out:
	mkdir out

.PHONY: clean
clean:
	rm -rf out