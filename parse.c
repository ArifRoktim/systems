#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/types.h>
#include <pwd.h>
#include <errno.h>
#include <fcntl.h>
#include "parse.h"
#include "builtin.h"

extern int loop;
extern char *vars[256][2];


char ** new_parse_args(char * s1, char * delim){
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

int fork_and_exec( char **args ){

  int f = fork();
  if(f){
    int status;
    wait(&status);
  } else {
    execvp( args[0], args );;
    printf("shell: %s: %s\n", args[0], strerror(errno));
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
  
  //print_str_arr( cmds );
  // then iterate throgh cmds and run each cmd
  char *cmd = *cmds;
  int n = 0;
  char **args;
  int bool_entered_loop;
  while( cmd ){

    //printf("You entered: %s\n", input);
    char *delim1 = ">";
    args = parse_args(cmd, delim1);
    bool_entered_loop = 1;
    //printf("Test!\n");
    //print_str_arr(args);

    // Check if have to redirect by seeing that args length is > 1
    if( args[1] ){
      //printf("Redirection: >\n");
      redirect(args, '>');
      n++;
      cmd = cmds[n];
      continue;
    }

    cmd = args[0];
    free(args);
    delim1 = "<";
    args = parse_args(cmd, delim1);

    // Check if have to redirect by seeing that args length is > 1
    if( args[1] ){
      //printf("Redirection: <\n");
      redirect(args, '<');
      n++;
      cmd = cmds[n];
      continue;
    }

    // Check for pipes
    cmd = args[0];
    free(args);
    delim1 = "|";
    args = parse_args(cmd, delim1);
    if( args[1] ){
      //printf("Redirection: |\n");
      redirect(args, '|');
      n++;
      cmd = cmds[n];
      continue;
    }
    
    // Else not redirecting so seperate by spaces
    char **old_args = args;
    args = parse_args(args[0], " ");
    free(old_args);
    
    // Check for builtin cmds
    if( do_builtins(args) ){
      // blank if statement as do_builtins has side effects
    }
    // Else args[0] is to be a cmd in the path
    else{
      // fork off and exec the command
      fork_and_exec( args );
    }

    // go to the next cmd
    n++;
    cmd = cmds[n];
  }
  free(cmds);
  if( bool_entered_loop )
    free(args);
}

void redirect(char **args, char direction){
  if( args[1] ){
    //printf("Redirection: %c\n", direction);
    int file;
    if( direction == '>' ){
      int file = open( args[1], O_CREAT | O_WRONLY | O_TRUNC , 0644 );
      dup_and_exec(args, file, direction);
    } else if( direction == '<' ){
      int file = open( args[1], O_RDONLY, 0 );
      dup_and_exec(args, file, direction);
    } else if( direction == '|' ){
      int file = -1;
      dup_and_exec(args, file, '|');
    }
  } else {
    printf("Syntax error!\n");
  }
}

void dup_and_exec( char **args, int file, char direction ){
  //printf("Forking\n");
  int f = fork();
  if(f){
    //printf("%d\n", f);
    int status;
    wait(&status);
  } else {
    //printf("%d\n", f);
    char **exec_args;
    if( direction == '>' ){
      dup2( file, STDOUT_FILENO );
      exec_args = parse_args(args[0], " ");
    } else if( direction == '<' ){
      dup2( file, STDIN_FILENO );
      exec_args = parse_args(args[0], " ");
    } else if( direction == '|'){
      FILE *pipe = popen(args[0], "r");
      dup2(fileno(pipe), STDIN_FILENO);
      exec_args = parse_args(args[1], " ");
    }
    //print_str_arr(exec_args);
    // Check for builtins and run them
    if( strstr(exec_args[0], "exit") ){
      //printf("Exiting!\n");
      exit(2);
    } else if( do_builtins(exec_args) ){
      //printf("Doing builtins!\n");
      exit(0);
    } else {
      //printf("Doing execvp!\n");
      execvp( exec_args[0], exec_args );
    }
    // if reached this point, error occurred with execing
    printf("Error: %s: %s\n", exec_args[0], strerror(errno));
    exit(1);
  }
}

char * trim( char *str ){
  while( *str && *str == ' ' ){
    str++;
  }
  char *temp = str + strlen(str) - 1;
  while( temp > str && *temp == ' ' ){
    *temp = 0;
  }
  return str;
}

char ** parse_args( char *line, char *delim ){
  int size = 5;
  char **args = (char **) malloc( size * sizeof(char *));
  int n = 0;
  while( line ){
    if( n + 1 > size || n == size ){
      size += 5;
      args = realloc( args, size * sizeof(char *));
    }
    args[n] = strsep( &line, delim);
    args[n] = trim(args[n]);
    n++;
  }
  args[n] = 0;
  return args;
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
