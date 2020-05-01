test: test.c ../seven_segment.c ../seven_segment.h out
	gcc -o out/test -Wall -Wextra -Werror -g test.c ../seven_segment.c -I ..
	./out/test

out:
	mkdir out

clean:
	rm -rf out