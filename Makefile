build:
	gcc -Wall -Werror -std=gnu11 -O2 -lm -o main src/main.c src/station.c

clean:
	rm -f main