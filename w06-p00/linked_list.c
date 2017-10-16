#include <stdio.h>
#include <stdlib.h>

struct node {
    char *name;
    char *artist;
    struct node *next;
};

struct node * insert_front( struct node *node, char *name, char *artist ){
    struct node *front = malloc( sizeof(struct node) );
    front->name = name;
    front->artist = artist;
    front->next = node;
    return front;
}

void print_list( struct node *list ){
    while( list ){
        printf("%s,%s->", list->name, list->artist );
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

int main(){
    struct node *llist = 0;
    llist = insert_front( llist, "is bob", "2" );
    llist = insert_front( llist, "bobbins", "1" );
    llist = insert_front( llist, "bob", "0" );

    print_list(llist);

    printf("Pointer to llist: %p\n", llist );
    printf("Pointer to llist after freeing: %p\n", llist = free_list(llist));

    print_list(llist);

    return 0;
}
