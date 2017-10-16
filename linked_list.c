#include <stdio.h>
#include <stdlib.h>

struct node {
    char *text;
    struct node *next;
};

struct node * insert_front( struct node *node, char *text ){
    struct node *front = malloc( sizeof(struct node) );
    front->text = text;
    front->next = node;
    return front;
}

void print_list( struct node *list ){
    while( list ){
        printf("%s->", list->text );
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
    llist = insert_front( llist, "is bob" );
    llist = insert_front( llist, "bobbins" );
    llist = insert_front( llist, "bob" );

    print_list(llist);

    printf("Pointer to llist: %p\n", llist );
    printf("Pointer to llist after freeing: %p\n", llist = free_list(llist));

    print_list(llist);

    return 0;
}
