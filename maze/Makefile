
.PHONY: clean

main: main.o maze.o
	gcc main.o maze.o -o main

main.o: main.c
	gcc -c main.c

maze.o: maze.c maze.h
	gcc -c maze.c

clean:
	rm *.o main