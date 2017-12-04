#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include "parse.h"
#include "builtin.h"
#include "misc.h"

int loop = 1;
char *vars[256][2];

int main( int argc, char *argv[] ){
  
  int i = 1;
  int bool_rainbow = 0;
  for(; i < argc; i++){
    if( !strcmp(argv[i], "-l") ){
      bool_rainbow = 1;
    }
  }

  if(bool_rainbow){
    rainbow();
  }
  
  // Run initialization stuff
  init();

  while(loop){
    print_prompt();
    fflush(stdout);
    char *input = get_input();

    if( input ){
      read_and_exec(input);
      free(input);
    }
  }

  // free stuff (and later save history)
  cleanup();

  return 0;
}
