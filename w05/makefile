all: my_string.o main.o
	gcc -o strtest my_string.o main.o

my_string.o: my_string.c my_string.h
	gcc -c my_string.c

main.o: main.c my_string.h
	gcc -c main.c

run: all
	./strtest

clean:
	rm *.o
