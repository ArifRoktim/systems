struct node {
    char *name;
    char *artist;
    struct node *next;
};
struct node * insert_front( struct node *node, char *artist, char *name );
void print_list( struct node *list );
struct node * free_list( struct node *list );
struct node * find( struct node *list, char *artist, char * name );
struct node * get_node( struct node * list, int index);
struct node * insert( struct node * list, int index, char *artist, char *name);
struct node * insert_at_node( struct node * node, char *artist, char *name );
struct node * insert_order( struct node *list, char *artist, char *name);
struct node * find_artist( struct node *list, char *artist );
struct node * rand_element( struct node *list );
struct node * insert_front( struct node *node, char *artist, char *name );
struct node * remove_song( struct node *list, char *artist, char *name );
void print_node( struct node *item );
