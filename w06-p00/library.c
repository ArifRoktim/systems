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

void print_letter( struct node *library[26], char letter){
  int index = tolower(letter) - 'a';
  print_list(library[index]);
}

struct node * find_artist_library( struct node *library[26], char *artist){
  int index = tolower(artist[0]) - 'a';
  return find_artist(library[index], artist);
}

void print_artist( struct node *library[26], char *artist){
  struct node *artists = find_artist_library(library, artist);
  while ( artists && !strcmp(artists -> artist, artist)){
    printf("[%s, %s],  ", artists -> artist, artists -> name);
    artists = artists -> next;
  }
  printf("NULL\n");
}

struct node * find_song( struct node *library[26], char *artist, char *name ){
    struct node *retNode = find_artist_library( library, artist );
    while( retNode ){
        if( strcmp(name, retNode->name) == 0 ){
            return retNode;
        }
        retNode = retNode->next;
    }
    return 0;
}

/*  
    Shuffle - print out a series of randomly chosen songs.
    Delete a song
    Delete all the nodes. */
