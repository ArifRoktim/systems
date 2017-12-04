//Clears global variable array responsible for holding shell variables 
//Reads and executes commands from ./.shellrc before prompting user  
void init();
//Frees the global variable array responsible for holding shell variables
void cleanup();
