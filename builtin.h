//Changes cwd to path described in dir  
void cd(char *dir);
//Echos the strings in args to STDOUT  
//Echos variables. Variables are denoted by a dollar sign in front of them
void echo(char **args);
//Prints the prompt(current working directory) at the beginning of each cycle of the shell
void print_prompt();
//Reads string from STDIN. Strips newlines and extraneous spaces. Returns cleaned string
char * get_input();
//Assigns value to shell variable _input_  
void assign_var(char *input);
//Determines whether cmd is a builtin command and if so runs it
int do_builtins( char **args );
