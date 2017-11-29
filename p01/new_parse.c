#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

/*
 *0.)made delim a (char *) bc of >> and << operators
 *1.)updated function to work without strip functions
 *2.)max size of buffer is now BUFSIZ
 * */
char ** parse_args(char * s1, char * delim){
	char ** ret = (char **) calloc (BUFSIZ, sizeof(char*));
	int i = 0;
	char * arg;

	while(i<BUFSIZ && s1){// note: s1 is null
		arg = strsep(&s1, delim);		
		if (*arg){//checks for extra delims, note: arg is empty
			ret[i] = arg; 
			i++;
		}
	}
	//maybe put a realloc here
	return ret;
}
int main(){
	printf("BUFSIZ = %d\n", BUFSIZ);
	//char * line = "ls -a -l";
	char line[100] = "  ls  -a -l";
	char * m = line;
	char ** test = parse_args(m, " ");
	execvp(test[0], test);
}
