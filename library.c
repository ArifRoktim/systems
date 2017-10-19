#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "linked_list.h"

struct node * create_library(){
    struct node * library = (struct node *) malloc( 27 * (sizeof (struct node *) ));
    return library;
}

struct node * add_song(struct node * library, char *artist, char *name){
    int index = tolower(artist[0]);
    printf("index: %d",index);
}
