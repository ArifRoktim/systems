#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "parse.h"
#include "builtin.h"
#include "misc.h"

int loop = 1;
char *vars[256][2];

int main( int argc, char *argv[] ){
  // Run initialization stuff
  int f = fork();
  if(f){
    int status;
    wait(&status);
  } else {
    init();
    exit(0);
  }

  while(loop){
    print_prompt();
    char *input = get_input();

    if( input ){
      f = fork();
      if(f){
        free(input);
        int status;
        wait(&status);
        if( WIFEXITED(status) && WEXITSTATUS(status) == 1 ){
          loop = 0;
        }
      } else {
        read_and_exec(input);
        exit(0);
      }
    }
  }

  // free stuff (and later save history)
  cleanup();

  return 0;
}
