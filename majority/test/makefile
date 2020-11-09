test: ../majority.h test_majority.c out
	gcc test_majority.c -g -o out/majority -Wall -Wextra -Werror -std=c99
	./out/majority

out:
	mkdir out

.PHONY: clean
clean:
	rm -rf out