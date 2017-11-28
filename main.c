#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "parse.h"
#include "builtin.h"
#include "misc.h"

int loop = 1;
char *vars[256][2];

int main( int argc, char *argv[] ){
  // Run initialization stuff
  init();

  while(loop){
    print_prompt();
    char *input = get_input();

    read_and_exec(input);
    free(input);
  }

  // free stuff (and later save history)
  cleanup();

  return 0;
}
