all: ./linked_list.o ./main.o
	gcc -Wall -g -o ./linked_list ./linked_list.o ./main.o

./linked_list.o: ./linked_list.c ./linked_list.h
	gcc -Wall -g -c ./linked_list.c

./main.o: ./main.c ./linked_list.h
	gcc -Wall -g -c ./main.c

run: all
	./linked_list

clean:
	rm *.o
