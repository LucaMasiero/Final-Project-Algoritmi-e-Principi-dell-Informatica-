build:
	gcc -Wall -Werror -std=gnu11 -O2 -lm -o main main.c

clean:
	rm -f main