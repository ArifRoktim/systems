all: main.o w11.o builtin.o
	gcc -o main main.o w11.o builtin.o

main.o: main.c
	gcc -c main.c

w11.o: w11.c
	gcc -c w11.c

builtin.o: builtin.c
	gcc -c builtin.c

run: all
	./main
