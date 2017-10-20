#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "linked_list.h"
#include "library.h"

int main(){
    struct node *llist = 0;
    printf("=============TESTING LLIST==============\n");
    printf("========TESTING insert_front()========\n");
    llist = insert_front( llist, "is bob", "lisa" );
    llist = insert_front( llist, "bobbins", "holmes" );
    llist = insert_front( llist, "bob", "doughnut" );

    print_list(llist);
    printf("\n\n");

    printf("========TESTING find()========\n");
    printf("[bobbins2] is at %p\n", find(llist, "bobbins2", "holmes"));
    printf("[bobbins] is at %p\n", find(llist, "bobbins", "holmes"));
    printf("\n\n");

    printf("========TESTING insert()========\n");
    llist = insert( llist, 1, "middle", "malcolm" );
    print_list(llist);

    llist = insert( llist, 0, "beginning", "the" );
    print_list(llist);
    printf("\n\n");

    printf("========TESTING insert_at_node()========\n");
    insert_at_node( find(llist,"bob","doughnut"), "test", "123" );
    print_list(llist);
    printf("\n\n");

    llist = free_list(llist);
    printf("Printing llist:");
    print_list(llist);

    //printf("%d\n",strcmp("a","b")); // -1

    printf("========Testing insert_order()==========\n");
    llist = insert_order( llist, "ELO", "Twilight" );
    print_list(llist);
    llist = insert_order( llist, "ELO", "Mr. Blue Sky" );
    print_list(llist);
    llist = insert_order( llist, "ELO", "Turn to Stone" );
    print_list(llist);
    llist = insert_order( llist, "ELO", "Shine a Little Love" );
    print_list(llist);
    llist = insert_order( llist, "ABBA", "Take a Chance on Me" );
    print_list(llist);
    llist = insert_order( llist, "ABBA", "Dancing Queen" );
    print_list(llist);
    llist = insert_order( llist, "ABBA", "Mamma Mia" );
    print_list(llist);
    printf("\n\n");

    printf("========Testing find_artist()========\n");
    print_list( find_artist(llist, "ELO") );
    printf("\n\n");

    printf("========Testing rand_element()========\n");
    srand(time(NULL));
    struct node *rand = rand_element( llist );
    printf("Random song is: [%s] by [%s]\n", rand->name, rand->artist);
    printf("\n\n");

    printf("========Testing remove_song()========\n");
    printf("Removing [Mamma Mia] by [ABBA].\n");
    llist = remove_song(llist, "ABBA", "Dancing Queen");;
    print_list(llist);
    printf("Removing [Mr. Blue Sky] by [ELO].\n");
    llist = remove_song(llist, "ELO", "Mr. Blue Sky");;
    print_list(llist);
    printf("\n\n");

    free_list(llist);

    struct node *library[26];
    instantiate( library );
    add_song( library, "ELO", "Twilight" );
    add_song( library, "ELO", "Mr. Blue Sky" );

    return 0;
}
