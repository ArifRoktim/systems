#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "linked_list.h"
#include "library.h"

void instantiate( struct node *library[26] ){
    int i = 0;
    for(; i <= 26; i++){
        library[i] = 0;
    }
}

void add_song(struct node *library[26], char *artist, char *name){
    int index = tolower(artist[0]) - 'a';
    library[index] = insert_order( library[index], artist, name );
}

void print_library( struct node *library[26] ){
    int i = 0;
    for(; i <=26; i++){
        if( library[i] ){
            printf("%c: ",i+'a');
            print_list( library[i] );
        }
    }
}
