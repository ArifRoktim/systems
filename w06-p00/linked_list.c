#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linked_list.h"

struct node {
    char *name;
    char *artist;
    struct node *next;
};

struct node * insert_front( struct node *node, char *artist, char *name ){
    struct node *front = (struct node *) malloc( sizeof(struct node) );
    front->name = name;
    front->artist = artist;
    front->next = node; return front;
}

void print_list( struct node *list ){
  while( list ){
        printf("%s, %s -> ", list->name, list->artist );
        list = list->next;
    }
    printf("NULL\n");
}

struct node * free_list( struct node *list ){
    while( list ){
        struct node *next = list->next;
        free(list);
        list = next;
    }
    return 0;
}

struct node * find( struct node *list, char *artist, char * name ){
  while( list ){
    if(strcmp( list->name, name ) == 0 && strcmp( list->artist, artist ) == 0){
      return list;
    }
    printf( "name: %s\n", list->name);
    printf( "next: %p\n\n", list->next);
    list = list->next;
  }
  return 0;
}

struct node * get_index( struct node * list, int index){
  int i = 0;
  for(; i < index; i++){
    list = list -> next;
  }
  return list;
}

struct node * insert( struct node * list, int index, char *artist, char *name){
    if( index == 0 ){
        return list = insert_front( list, artist, name );
    }
    struct node *new = (struct node*) malloc( sizeof(struct node) );
    new->artist = artist;
    new->name = name;
    struct node *before = get_index( list, index - 1 );
    if( before->next == 0 ){
        new->next = 0;
        before->next = new;
    } else {
        struct node *temp = before->next;
        before->next = new;
        new->next = temp;
    }
    return list;
}

struct node * insert_order( struct node *list, char *artist, char *name){
  if(!list){
    return insert_front(list, artist, name); } while (strcmp ( list -> artist, artist) > 0){
    list = list -> next;
  }
}
	

int main(){
    struct node *llist = 0;
    llist = insert_front( llist, "is bob", "2" );
    llist = insert_front( llist, "bobbins", "1" );
    llist = insert_front( llist, "bob", "0" );

    print_list(llist);

    printf("[bobbins2] is at %p\n", find(llist, "bobbins2", "1"));
    printf("[bobbins] is at %p\n", find(llist, "bobbins", "1"));

    llist = insert( llist, 1, "middle", "malcolm" );
    print_list(llist);

    llist = insert( llist, 0, "beginning", "the" );
    print_list(llist);

    //insert( llist, 1, "end", "the" );
    //print_list(llist);


    return 0;
}
