all: ./linked_list.c
	gcc -Wall -g -o ./linked_list ./linked_list.c

run: all
	./linked_list
