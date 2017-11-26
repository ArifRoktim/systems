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

int fork_and_exec( char *program, char **args ){
  int f = fork();
  if(f){
    int status;
    wait(&status);
  } else {
    execvp( program, args );;
  }
  return -1;
}

void read_and_exec( char* input ){

  //printf("Input 1: %s\n", input);
  // first seperate based on semicolons
  char *delim0 = ";";
  char **cmds = parse_args(input, delim0);
  //printf("Input 2: %s\n", input);
  
  //print_str_arr( cmds );
  // then iterate throgh cmds and run each cmd
  char *cmd = *cmds;
  int n = 0;
  while( cmd ){

    //printf("You entered: %s\n", input);
    char *delim1 = " ";
    char **args = parse_args(cmd, delim1);
    //print_str_arr(args);

    // Check if cmd is a builtin function first
    // Check if exiting
    if( !strcmp(args[0], "exit") ){
      exit(0);
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
    // Else args[0] is to be a cmd in the path
    else{
      // fork off and exec the command
      fork_and_exec( args[0], args );
    }

    // go to the next cmd
    n++;
    cmd = cmds[n];
  }
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
  char *ret = (char *) calloc(1, size);
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
  return ret;
}
