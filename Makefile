start: main
	./main

build: array_utils.c comparators.c input.c menu.c main.c
	gcc array_utils.c comparators.c input.c menu.c main.c -o main
