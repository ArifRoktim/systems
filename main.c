#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "w11.h"
#include "builtin.h"

void strip_newline( char *str ){
  while( *str ){
    if( *str == '\n' ){
      *str = 0;
    }
    str++;
  }
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

int main( int argc, int *argv[] ){

  int loop = 1;
  while(loop){
    char input[100];
    printf("$ ");
    fgets(input, sizeof(input), stdin);
    strip_newline(input);

    read_and_exec(input);
  }
}
