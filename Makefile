
START=0

all: solver unittest

run: solver
	LD_LIBRARY_PATH=. ./solver $(START)

test: unittest
	LD_LIBRARY_PATH=. ./unittest

solver: solver.o libpuzzle.so
	gcc solver.o -L. -lpuzzle -o solver

solver.o : puzzle.h solver.c
	gcc -std=c99 -Wall -c solver.c

unittest: unittest.o libpuzzle.so 
	gcc unittest.o -L. -lpuzzle -o unittest

unittest.o : puzzle.h unittest.c
	gcc -std=c99 -Wall -c unittest.c

libpuzzle.so: puzzle.o
	gcc -shared -Wl,-soname,libpuzzle.so -o libpuzzle.so puzzle.o

puzzle.o: puzzle.c
	gcc -fPIC -std=c99 -Wall -c puzzle.c

