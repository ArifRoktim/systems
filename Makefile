all: main.o parse.o builtin.o
	gcc -g -o main main.o parse.o builtin.o

main.o: main.c
	gcc -g -c main.c

parse.o: parse.c
	gcc -g -c parse.c

builtin.o: builtin.c
	gcc -g -c builtin.c

run: all
	./main

clean:
	rm -f main *.o
