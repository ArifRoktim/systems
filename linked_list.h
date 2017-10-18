struct node * insert_front( struct node *node, char *artist, char *name );
void print_list( struct node *list );
struct node * free_list( struct node *list );
struct node * find( struct node *list, char *artist, char * name );
struct node * get_index( struct node * list, int index);
struct node * insert( struct node * list, int index, char *artist, char *name);
struct node * insert_order( struct node *list, char *artist, char *name);