# p01
Shell Project  
by Arif Roktim and Daniel Regassa  

Features:  
* Forks and executes commands
* Parses multiple commands on one line
* Gets rid of extraneous spaces between tokens
* Redirects using >, < and |
  * Supports append redirection `>>`
  * Supports double redirection `cmd < foo > bar`
* Shell variables! Uses bash syntax
  * Set variables using `varname=varvalue`
    * Var value can't have spaces in it
  * Can echo variables using `echo $varname`
* Reads and executes from a file called _.shellrc_ at startup
* Lolcat mode! If "-l" flag passed to main and lolcat installed, will output everything rainbow!
  * Picture of it working:
![Picture of loclat mode working](https://i.imgur.com/G2hHlmd.png)

Attempted:
* A more efficient parse_args() function called new_parse_args(), too lazy to rewrite code to accomadate it
* The ability to have spaces in variable values. Attempted to replace all space occurences with the value -1 and then after using parse_args replace all -1s with a space but didn't work and was too lazy to debug
* Have shell read from PS1 variable to set prompt

Bugs:
* Variables cant have spaces in their value
* Doesn't support redirection with pipes `ls | sort -r > foo`
* Lolcat mode 
  * Can't exit in lolcat mode
  * Doesnt print prompt until you hit enter
  * Sometimes get encoding errors with lolcat `invalid byte sequence in UTF-8 (ArgumentError)`
    * Happens when doing things such as `$ cat /dev/random`

Files & Function Headers:  

## builtin.c

Handles functions that are not forked before executing

### void cd()
Inputs:  char \* dir  
Returns: Nothing  
Changes cwd to path described in dir  

### void echo()
Inputs:  char \*\* args  
Returns: Nothing  
Echos the strings in args to STDOUT  
Echos variables. Variables are denoted by a dollar sign in front of them

### void print_prompt()
Inputs:  None  
Returns: Nothing  
Prints the prompt(current working directory) at the beginning of each cycle of the shell

### char \* get\_input() 
Inputs:  None  
Returns: User input (commands)  
Reads string from STDIN. Strips newlines and extraneous spaces. Returns cleaned string
  
### void print\_prompt() 
Inputs:  None  
Returns: Nothing  
Prints the prompt(current working directory) at the beginning of each cycle of the shell  
  
### void assign\_var()
Inputs:  char \* input  
Returns: Nothing  
Assigns value to shell variable _input_  
  
### int do\_builtins()
Inputs:  char \*\* args  
Returns: 1 if command is echo, cd, exit, or variable assignment  
0 otherwise  
Determines whether cmd is a builtin command and if so runs it
  

## misc.c

Miscellaneous functions
  
### void init()
Inputs:  None  
Returns: Nothing  
Clears global variable array responsible for holding shell variables  
Reads and executes commands from ./.shellrc before prompting user  
  
### void cleanup()
Inputs:  None  
Returns: Nothing  
Frees the global variable array responsible for holding shell variables

### void rainbow()
Inputs:  None  
Outputs: Nothing  
Makes a pipe and forks. Parent opens pipe and redirects stdout to pipe.  
Child opens pipe and redirects stdin to pipe. Forks and execs lolcat.  
Result is that stdout output is rainbow  

## parse.c

Handles parsing of input

### char \*\* parse\_args()
Inputs: char \* line 	The string passed in from user through get_input() or ./.shellrc  
char \* delim	One of ' ' , ';' , '>', '<', '|'  
Returns:  A null-terminated array of null-terminated strings that is the result of parsing line by delim. 

First used to parse line into commands by semicolon delimiter.  
Then used to split commands for redirection.  
Then used to parse commands into tokens by delimiter ' '
	
### void print\_str\_arr()
Inputs: char \*\* arr  
Returns:  Nothing  
Prints a string array that ends in null. Used for diagnostics
	
### void strip\_newline()
Inputs: char \* str  
Returns:  Nothing  
Changes all newlines in str to null character
	
### char \* strip\_spaces()
Inputs: char \* str  
Returns: Returns a new string that has no extra spaces:  
either consecutive, leading, or trailing
    
### int fork\_and\_exec()
Inputs: char \*\* args  
Returns: 1 if sucessfull  
Forks off a child and makes it execute exevp(args[0], args)
	
### void read\_and\_exec()
Inputs: char \* input  
Returns: Nothing  
The main parsing function. Seperates input first by semicolons.  
Then seperates input by redirection symbols (i.e., "><|")  
Then seperates cmds into tokens by space
Runs redirection, builtins, and cmds in PATH
	
### void redirect()
Inputs: char \*\*args, char direction (either '>', '<', or '|')  
Returns: Nothing  
Reads _direction_ and if necessary opens the correct file. Then runs _dup\_and\_exec_
	
### void dup\_and\_exec()
Inputs:  char \*\*args, int file_descriptor, char direction (either '>' or '<')  
Returns: Nothing  
Reads _direction_ and then _fork_ s and _dup2_ s accordingly. Then _execvp_ s cmd
    
