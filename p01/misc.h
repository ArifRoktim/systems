//Clears global variable array responsible for holding shell variables 
//Reads and executes commands from ./.shellrc before prompting user  
void init();
//Frees the global variable array responsible for holding shell variables
void cleanup();
//Makes a pipe and forks. Parent opens pipe and redirects stdout to pipe.
//Child opens pipe and redirects stdin to pipe. Forks and execs lolcat
//Result is that stdout output is rainbow
void rainbow();
