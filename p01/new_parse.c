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
void print_bytes(char * str, int size){
	int i = 0;
	printf("\n[");
	char to_print;
	for (;i<size;i++){
		//printf("%i", i);
		to_print = str[i];
		if (to_print == 0){
			printf("/0");
		}
		else if (to_print == ' '){
			printf("_");
		}
		else{
			printf("%c", to_print);
		}
	}
	printf("]\n");
}

int main(){
	printf("BUFSIZ = %d\n", BUFSIZ);
	//char * line = "ls -a -l";
	char line[100] = "ls > foo.txt";
	char * m = line;
	char ** test = parse_args(m, ">");
	
	//printf("%s", line);
	int i = 0;
	for (;i<2;i++){
		printf("%s", test[i]);
	}
//	print_bytes(line, 100);
	printf('\n');
}
