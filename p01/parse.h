// Parse args from hw11 but with parameter to say what to delimit by.
// Used to seperate cmds based by semilcolons first
// and then seperate tokens in each cmd
char ** parse_args( char *line, char *delim );
// Prints a string array that ends in null. Used for diagnostics
void print_str_arr( char **arr );
// Modifies all newlines to become null
void strip_newline( char *str );
// Returns a new string that has no extra spaces
// i.e, no multiple consecutive spaces or spaces after semicolons
char * strip_spaces( char *str );


int fork_and_exec( char *program, char **args );
void read_and_exec( char* input );
