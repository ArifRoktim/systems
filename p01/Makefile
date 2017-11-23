all: main.o w11.o builtin.o
	gcc -g -o main main.o w11.o builtin.o

main.o: main.c
	gcc -g -c main.c

w11.o: w11.c
	gcc -g -c w11.c

builtin.o: builtin.c
	gcc -g -c builtin.c

run: all
	./main
