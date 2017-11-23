#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include "builtin.h"
#include "w11.h"

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

  // first seperate based on semicolons
  char **cmds = parse_args(input, ';');
  
  //print_str_arr( cmds );
  // then iterate throgh cmds and run each cmd
  char *cmd = *cmds;
  int n = 0;
  while( cmd ){

    //printf("You entered: %s\n", input);
    char **args = parse_args(cmd, ' ');
    print_str_arr(args);

    // fork off and exec the command
    fork_and_exec( args[0], args );

    // go to the next cmd
    n++;
    cmd = cmds[n];
  }
}
