all: ./w08.c
	gcc -g -o w08 ./w08.c

run: all
	./w08
