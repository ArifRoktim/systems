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
}

int main(){
    struct node *llist;
}
