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
//Forks off a child and makes it execute exevp(args[0], args)
int fork_and_exec( char **args );
/*
The main parsing function. Seperates input first by semicolons.  
Then seperates input by redirection symbols (i.e., "><|")  
Then seperates cmds into tokens by space
Runs redirection, builtins, and cmds in PATH
 */
void read_and_exec( char* input );
//Reads direction and if necessary opens the correct file. Then runs dup_and_exec
void redirect(char **args, char direction);
//Reads direction and then forks and dup2s accordingly. Then execvps cmd
void dup_and_exec( char **args, int file, char direction );
