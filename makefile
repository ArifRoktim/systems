all: ./w11.c
	gcc -o w11 w11.c

run: all
	./w11
