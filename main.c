#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "parse.h"
#include "builtin.h"

int main( int argc, char *argv[] ){

  int main_loop = 1;
  while(main_loop){
    print_prompt();
    char *input = get_input();

    read_and_exec(input);
    free(input);
  }
  return 0;
}
