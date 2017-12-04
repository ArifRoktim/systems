# p01
Shell Project
by Arif Roktim and Daniel Regassa

Features:
	Forks and executes commands!
	Parses multiple commands on one line!
	Redirects using >, <!

Attempted:
	A more efficient parse_args() function called new_parse_args(), too lazy to rewrite code to accomadate it

Bugs:
	echo'ing two arguments will print them without a space
	
Files & Function Headers:

builtin.c
	Handles functions that are not forked before executing
	/*======== void cd() ==========
	Inputs:  char * dir 
	Returns: Nothing
 
  	Changes cwd to path described in dir
	====================*/

	/*======== void echo() ==========
	Inputs:  char ** args
	Returns: Nothing
  
  	Echos the strings in args to STDOUT
	====================*/

	/*======== void print_prompt() ==========
	Inputs:  None 
	Returns: Nothing

	Prints the prompt(current working directory) at the beginning of each cycle of the shell 
	====================*/

	/*======== char * get_input() ==========
	Inputs:  None 
	Returns: User input (commands)

	Reads string from STDIN 
	====================*/
  
  /*======== void print_prompt() ==========
	Inputs:  None 
	Returns: Nothing

	Prints the prompt(current working directory) at the beginning of each cycle of the shell 
	====================*/
  
  /*======== void assign_var() ==========
	Inputs:  char * input 
	Returns: Nothing

	Assigns value to shell variable input 
	====================*/
  
  /*======== int do_builtins() ==========
	Inputs:  char ** args
	Returns: 1 if command is echo, cd, exit, or variable assignment
           0 otherwise

	Determines whether child should be forked to run command
	====================*/
  
 

misc.c
	Handles necessary initialization and cleanup required for shell
  
  /*======== void init() ==========
	Inputs:  None
	Returns: Nothing

	Clears global variable array responsible for holding shell variables
	Reads and executes commands from ./.shellrc before prompting user
	====================*/
  
  /*======== void cleanup() ==========
	Inputs:  None
	Returns: Nothing

	Frees the global variable array responsible for holding shell variables
	====================*/


parse.c
  /*======== char ** parse_args() ==========
	Inputs: char * line 	The string passed in from user through get_input() or ./.shellrc
		char * delim	One of ' ' , ';' , '>', '<', '|'
	Returns:  An array of null-terminated strings that is the result of parsing line by delim

	First used to parse line into commands by semicolon delimiter
	Then used to parse commands into tokens by delimiter ' '
	====================*/
	
  /*======== void print_str_arr() ==========
	Inputs: char ** arr   	
	Returns:  Nothing
	
	Prints a string array that ends in null. Used for diagnostics
	====================*/
	
  /*======== void strip_newline() ==========
	Inputs: char * str  	
	Returns:  Nothing
	
	Changes all newlines in str to null character
	====================*/
	
  /*======== char * strip_spaces() ==========
	Inputs: char * str
	Returns: Returns a new string that has no extra spaces
		either consecutive, leading, or trailing
	
	====================*/
	
  /*======== int fork_and_exec() ==========
	Inputs: char ** args
	Returns: 1 if sucessfull
	
	Forks off a child and makes it execute exevp(args[0], args)
	====================*/	
	
 /*======== void read_and_exec() ==========
	Inputs: char * input
	Returns: Nothing
	
	
	====================*/
	
/*======== void redirect() ==========
	Inputs: char **args, char direction (either '>' or '<')
	Returns: Nothing
	
	Redirects 
	====================*/
	
/*======== void dup_and_exec() ==========
	Inputs:  char **args, int file_descriptor, char direction (either '>' or '<')
	Returns: Nothing
	
	
	====================*/
	
