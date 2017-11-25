all: main.o parse.o
	gcc -g -o main main.o parse.o

main.o: main.c
	gcc -g -c main.c

parse.o: parse.c
	gcc -g -c parse.c

run: all
	./main

clean:
	rm -f main *.o
