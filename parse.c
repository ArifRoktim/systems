#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/types.h>
#include <pwd.h>
#include <errno.h>
#include "parse.h"
#include "builtin.h"

extern int loop;
extern char *vars[256][2];

int fork_and_exec( char *program, char **args ){
  int f = fork();
  if(f){
    int status;
    wait(&status);
  } else {
    execvp( program, args );;
    printf("shell: %s: %s\n", program, strerror(errno));
    exit(1);
  }
  return 1;
}

void read_and_exec( char* input ){
  // If input blank, do nothing
  if( ! strcmp(input,"") )
    return;

  //printf("Input 1: %s\n", input);
  // first seperate based on semicolons
  char *delim0 = ";";
  char **cmds = parse_args(input, delim0);
  //printf("Input 2: %s\n", input);
  
  //printf("Hey o!\n");
  //print_str_arr( cmds );
  // then iterate throgh cmds and run each cmd
  char *cmd = *cmds;
  int n = 0;
  char **args;
  int bool_entered_loop;
  while( cmd ){

    //printf("You entered: %s\n", input);
    char *delim1 = " ";
    args = parse_args(cmd, delim1);
    if( args[0] == NULL ){
      //printf("Uh oh!\n");
      break;
    }
    bool_entered_loop = 1;
    //print_str_arr(args);

    // Check if cmd is a builtin function first
    // Check if exiting
    if( !strcmp(args[0], "exit") ){
      loop = 0;
    }
    // Check if cd-ing
    else if( !strcmp(args[0], "cd") ){
      if( args[1] ){
        cd(args[1]);
      } else {
        struct passwd *pw = getpwuid(getuid());
        cd(pw->pw_dir);
      }
    }
    // Check if echo-ing
    else if( !strcmp(args[0], "echo") ){
      echo(args);
    }
    // Check if assigning a variable
    else if( strchr(args[0], '=') && (strstr(args[0], "\\=") == NULL) ){
      //printf("Heyyooo! Assigned!\n");
      assign_var(args[0]);
    }
    // Else args[0] is to be a cmd in the path
    else{
      // fork off and exec the command
      fork_and_exec( args[0], args );
    }

    // go to the next cmd
    n++;
    cmd = cmds[n];
  }
  free(cmds);
  if( bool_entered_loop )
    free(args);
}


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

void print_str_arr( char **arr ){
  char *str = *arr;
  int n = 0;
  while( str ){
    n++;
    printf("%d:\t%s\n", n-1, str );
    str = *(arr + n);
  }
}

void strip_newline( char *str ){
  while( *str ){
    if( *str == '\n' ){
      *str = 0;
    }
    str++;
  }
}

// returns new string
char * strip_spaces( char *str ){
  int size = strlen(str);
  char *ret = (char *) calloc(1, size + 1);
  char tmp[size];
  int i = 0;
  for(; i < size; i++){
    tmp[i] = 0;
  }
  i = 0;
  int j = 0;
  // first remove consecutive spaces
  while( i + j < size ){
    if(str[i+j] == ' ' && (i+j+1 < size) && str[i+j+1] == ' '){
      tmp[i] = ' ';
      i++;
      while(str[i+j] == ' '){
        j++;
      }
    } else {
      tmp[i] = str[i + j];
      i++;
    }
  }
  // then remove spaces around semicolons
  i = j = 0;
  while( i + j < size ){
    if(tmp[i+j] == ' ' && (i+j+1 < size) && tmp[i+j+1] == ';'){
      ret[i] = ';';
      i++;
      j++;
    } else if(tmp[i+j] == ' ' && (i+j-1 >= 0) && tmp[i+j-1] == ';'){
      j++;
    } else {
      ret[i] = tmp[i + j];
      i++;
    }
  }
  // remove trailer and leading spaces
  // keep track of old calloc'd memory
  char *ptr = ret;
  // move to first non space character
  while( *ptr && *ptr == ' ' ){
    ptr++;
  }
  char *temp = ptr + strlen(ptr) - 1;
  while( temp > ptr && *temp == ' ' ){
    *temp = 0;
  }
  char temp2[strlen(ptr)];
  strcpy(temp2, ptr);
  strcpy(ret, temp2);
  return ret;
  //return old;
  // strip leading and trailing spaces
}
