#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "w11.h"
#include "builtin.h"

int main( int argc, int *argv[] ){

  int loop = 1;
  while(loop){
    char input[100];
    printf("$ ");
    fgets(input, sizeof(input), stdin);
    printf("You entered: %s", input);
    char **args = parse_args(input);
    //print_str_arr(args);
    // fork off and exec the command
    fork_and_exec( args[0], args );
  }
}
