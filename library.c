#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "linked_list.h"
#include "library.h"

void instantiate( struct node *library[26] ){
    int i = 0;
    for(; i <= 26; i++){
        library[i] = 0;
    }
}

struct node * add_song(struct node *library[26], char *artist, char *name){
    int index = tolower(artist[0]) - 'a';
    printf("index: %d\n",index);
    if( library[index] ){
        insert_order( library[index], artist, name );
    } else {
        struct node new;
        new.name=name;
        new.artist=artist;
        new.next=0;
        library[index] = &new;
    }
}
