#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "linked_list.h"
#include "library.h"

struct node * add_song(struct node *library[26], char *artist, char *name){
    int index = tolower(artist[0]) - 'a';
    printf("index: %d\n",index);

}
