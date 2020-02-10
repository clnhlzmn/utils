test: test_crc.c ../crc16.h ../crc16.c ../crc32.h ../crc32.c out
	gcc -o out/test -Wall -Wextra -Werror -g test_crc.c ../crc16.c ../crc32.c
	./out/test

out:
	mkdir out

clean:
	rm -rf out