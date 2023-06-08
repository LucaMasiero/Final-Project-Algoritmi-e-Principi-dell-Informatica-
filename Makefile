CC = gcc
CFLAGS = -Wall -Werror -std=gnu11 -O2 -g3 -lm
FSAN = -fsanitize=address

all: build

build: src/main.c
	 $(CC) $(CFLAGS) $(FSAN) src/main.c src/station.c src/find_path.c src/vehicle.c -o main

# ------------- Remember to disable address sanitizer when using valgrind -------------
#### DEBUGGING ####
valgrind:
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./main

#### OPTIMISATION ####
callgrind:
	valgrind --tool=callgrind --callgrind-out-file=callgrind_out ./main
	kcachegrind callgrind_out

massif:
	valgrind --tool=massif --massif-out-file=massif_out ./main
	massif-visualizer massif_out

time:
	/usr/bin/time ./main


clean:
	rm -f main
	rm -f *.o
