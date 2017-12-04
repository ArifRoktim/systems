#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <pwd.h>
#include "builtin.h"
#include "parse.h"

extern int loop;
extern char *vars[256][2];

int do_builtins( char **args ){
	// Check if exiting
	if( !strcmp(args[0], "exit") ){
		loop = 0;
		return 1;
	}
	// Check if cd-ing
	else if( !strcmp(args[0], "cd") ){
		if( args[1] ){
			cd(args[1]);
		} else {
			struct passwd *pw = getpwuid(getuid());
			cd(pw->pw_dir);
		}
		return 1;
	}
	// Check if echo-ing
	else if( !strcmp(args[0], "echo") ){
		echo(args);
		return 1;
	}
	// Check if assigning a variable
	else if( strchr(args[0], '=') && (strstr(args[0], "\\=") == NULL) ){
		//printf("Heyyooo! Assigned!\n");
		assign_var(args[0]);
		return 1;
	}
	return 0;
}

void cd(char *dir){
	int status = chdir(dir);
	if(status){
		printf("shell: cd: %s: %s\n", dir, strerror(errno));
	}
}

void print_prompt(){
	// Get user's cwd
	char cwd[256];
	getcwd(cwd, sizeof(cwd));
	// Replace the home directory path with '~'

	
	printf("%s $ ", cwd);
}

char * get_input(){
	char raw_input[100];
	if( fgets(raw_input, sizeof(raw_input), stdin) == NULL ){
		loop = 0;
		return NULL;
	}
	strip_newline(raw_input);
	char *input = strip_spaces(raw_input);
	//printf("Raw: %s\nInput: %s\n", raw_input, input);
	//printf("Input 0: %s\n", input);
	return input;
}

void assign_var(char *input){
	char *delim = "=";
	char *name = strsep( &input, delim);
	int i = 0;
	if( strchr( input, '=') ){
		printf("shell: Invalid syntax\n");
		return;
	}
	int bool_exists = 0;
	while( i < 256 ){
		if( vars[i][0] ){
			if( !strcmp( vars[i][0], name) ){
				bool_exists = 1;
				break;
			} else {
				i++;
			}
		} else {
			break;
		}
	}
	//printf("%d\n",i);
	//printf("Name: %s\nInput: %s\n", name, input);
	char *m_name, *m_input;
	if( bool_exists ){
		m_name = vars[i][0];
		free(vars[i][1]);
	} else {
		m_name = (char *) malloc( strlen(name) * sizeof(char *) );
		strcpy(m_name, name);
	}
	m_input = (char *) malloc( strlen(input) * sizeof(char *) );
	strcpy(m_input, input);
	vars[i][0] = m_name;
	vars[i][1] = m_input;
}

void print_var(char *var){
	char *delim = "$";
	strsep(&var, delim);
	int i = 0;
	while( i < 256 && vars[i][0] ){
		if( !strcmp(vars[i][0], var) ){
			break;
		}
		i++;
	}
	if( vars[i][0] ){
		printf("%s",vars[i][1]);
	}
}

void echo(char **args){
	char *str = *args;
	int i = 0;
	while( str ){
		if(i != 0){
			// Check for dollar sign
			if( strchr(str, '$') ){
				//printf("Print variable");
				print_var(str);
			} else {
				printf("%s ", str);
			}
		}
		i++;
		str = *(args + i);
	}
	printf("\n");
}
