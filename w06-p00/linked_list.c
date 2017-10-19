#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linked_list.h"

struct node {
    char *name;
    char *artist;
    struct node *next;
};

/* Inserts node at front of list. Returns the added node.
 * Usage:
 * node = insert_front( node, "foo", "bar" );
 */
struct node * insert_front( struct node *node, char *artist, char *name ){
    struct node *front = (struct node *) malloc( sizeof(struct node) );
    front->name = name;
    front->artist = artist;
    front->next = node; 
    return front;
}

// Prints linked list
void print_list( struct node *list ){
  while( list ){
        printf("[%s, %s] -> ", list->artist, list->name );
        list = list->next;
    }
    printf("NULL\n");
}

// Frees linked list. Returns null pointer.
struct node * free_list( struct node *list ){
    while( list ){
        struct node *next = list->next;
        free(list);
        list = next;
    }
    return 0;
}

// Returns pointer to node in linked list with artist and name.
// Returns null pointer if not found.
struct node * find( struct node *list, char *artist, char * name ){
  while( list ){
    if(strcmp( list->name, name ) == 0 && strcmp( list->artist, artist ) == 0){
      return list;
    }
    //printf( "name: %s\n", list->name);
    //printf( "next: %p\n\n", list->next);
    list = list->next;
  }
  return 0;
}

// Returns node with index index
struct node * get_node( struct node * list, int index){
  int i = 0;
  for(; i < index; i++){
    list = list -> next;
  }
  return list;
}

// Inserts a node at index index. Returns the beginning of the list.
// Usage:
// node = insert( node, <index>, "foo", "bar" );
struct node * insert( struct node * list, int index, char *artist, char *name){
    if( index == 0 ){
        return list = insert_front( list, artist, name );
    }
    struct node *new = (struct node*) malloc( sizeof(struct node) );
    new->artist = artist;
    new->name = name;
    struct node *before = get_node( list, index - 1 );
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

// Adds a node after the given node. Returns the added node.
// Usage:
// insert_at_node( node, "foo", "bar" );
struct node * insert_at_node( struct node * node, char *artist, char *name ){
    struct node *new = (struct node *) malloc(sizeof(struct node));
    new->artist = artist;
    new->name = name;
    new->next=node->next;
    node->next = new;
    return new;
}

struct node * insert_order( struct node *list, char *artist, char *name){
  if(!list){
    return insert_front(list, artist, name); 
  } 
  while (strcmp ( list -> artist, artist) > 0){
    list = list -> next;
  }
}
	

int main(){
    struct node *llist = 0;
    llist = insert_front( llist, "is bob", "lisa" );
    llist = insert_front( llist, "bobbins", "holmes" );
    llist = insert_front( llist, "bob", "doughnut" );

    print_list(llist);

    printf("[bobbins2] is at %p\n", find(llist, "bobbins2", "holmes"));
    printf("[bobbins] is at %p\n", find(llist, "bobbins", "holmes"));

    llist = insert( llist, 1, "middle", "malcolm" );
    print_list(llist);

    llist = insert( llist, 0, "beginning", "the" );
    print_list(llist);

    insert_at_node( find(llist,"bob","doughnut"), "test", "123" );
    //insert( llist, 1, "end", "the" );
    print_list(llist);


    return 0;
}
