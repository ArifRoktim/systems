#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
    char *name;
    char *artist;
    struct node *next;
};

struct node * insert_front( struct node *node, char *artist, char *name ){
    struct node *front = malloc( sizeof(struct node) );
    front->name = name;
    front->artist = artist;
    front->next = node;
    return front;
}

void print_list( struct node *list ){
  while( list ){
        printf("%s,%s -> ", list->name, list->artist );
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
  list = NULL;
  while( printf("STUFFS\n") && list && printf("MORESTUTFFS\n") ){
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
  }return list;
}

struct node * insert( struct node * list, int index, char *artist, char *name){
  
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
    llist = insert_front( llist, "is bob", "2" );
    llist = insert_front( llist, "bobbins", "1" );
    llist = insert_front( llist, "bob", "0" );

    print_list(llist);

    printf("[bobbins] is at %p and is %s\n", find(llist, "bobbins2", "1"), find(llist, "bobbins2", "1")->artist);
    //printf("Pointer to llist: %p\n", llist );
    //printf("Pointer to llist after freeing: %p\n", llist = free_list(llist));

    //print_list(llist);

    printf("\n\n'a' -> 'b' : %d\n", strcmp("a", "b"));

    //printf("\n\n[bobbins] : %s\n", get_index(llist, 1) -> artist);

    return 0;
}
