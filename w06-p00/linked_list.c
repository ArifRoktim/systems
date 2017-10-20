#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linked_list.h"

/* Inserts node at front of list. Returns the added node.
 * Usage:
 * node = insert_front( node, "foo", "bar" ); */
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
    printf("========Freeing list========\n");
    while( list ){
        printf("Free'd [%s] by [%s]\n", list->name, list->artist);
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

// Inserts songs in order by artist and name. Returns beginning of list.
// Usage:
// list = insert_order( list, "foo", "bar" );
struct node * insert_order( struct node *list, char *artist, char *name){
  struct node *temp = list;
  if(!list){
    return insert_front(list, artist, name); 
  } printf("list->artist:%s\nartist:%s\nstrcmp():%d\n",list->artist,artist,
	   strcmp( list->artist, artist) );
  while( list->next != 0 && strcmp( list -> artist, artist) < 0){
    printf("list->artist:%s\nartist:%s\nstrcmp():%d\n",list->artist,artist,
	   strcmp( list->artist, artist) );
    list = list -> next;
  }
  while( list->next != 0 && strcmp( list->name, name ) > 0 ){
    list = list -> next;
  }
  insert_at_node( list, artist, name );
  return temp;
}

// Returns the node of the first song of an artist in list
struct node * find_artist( struct node *list, char *artist ){
    while( list ){
        if( strcmp( list->artist, artist ) == 0 ){
            return list;
        }
        list = list->next;
    }
    return 0;
}

// Returns a random element from the list.
// Note: Elements are not all equally likely to be chosen but still random.
struct node * rand_element( struct node *list ){
    while( list->next ){
        // Get rand double between 0 and 1
        double r = (double)rand() / (double) RAND_MAX;
        printf("%lf\n",r);
        if(r < 0.25){
            return list;
        }
        list = list->next;
    }
    return list;
}

// Removes given song.
// Returns node to beginning of list.
// Usage:
// llist = remove_song( llist, "foo", "bar" );
struct node * remove_song( struct node *list, char *artist, char *name ){
    struct node *front = list;
    if( strcmp(list->name, name) == 0 && strcmp(list->artist, artist) == 0 ){
        //printf("First!");
        struct node *temp = list;
        list = list->next;
        free(temp);
        return list;
    }
    while( list->next ){
        if( strcmp(list->next->name, name) == 0 && strcmp(list->next->artist, artist) == 0 ){
            struct node *temp = list->next;
            list->next = list->next->next;
            free(temp);
            return front;
        }
        list = list->next;
    }
    return front;
}

/*
You should start by making your linked lists work with the following functionality:
insert nodes at the front [done]
insert nodes in order [done]
print the entire list [done]
find and return a pointer to a node based on artist and song name [done]
find and return a pointer to the first song of an artist based on artist name [done]
Return a pointer to random element in the list. [done]
remove a single specified node from the list [done]
free the entire list [done]
*/
