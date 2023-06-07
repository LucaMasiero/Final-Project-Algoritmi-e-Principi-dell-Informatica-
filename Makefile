build:
	gcc -Wall -Werror -std=gnu11 -O2 -lm -o main src/main.c src/station.c src/find_path.c -fsanitize=address

# ------------- Remember to disable address sanitizer when using valgrind -------------
#### DEBUGGING ####
valgrind:
	echo ("memcheck")
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