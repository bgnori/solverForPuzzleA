

all: solver

solver: solver.c
	gcc -std=c99 -Wall -o solver solver.c
