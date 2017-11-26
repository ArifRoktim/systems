#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "parse.h"
#include "builtin.h"

int loop = 1;
char *vars[256][2];

int main( int argc, char *argv[] ){
  // Blank out variables array
  int i = 0;
  int j = 0;
  for(; i < 256; i++){
    for(; j < 2; j++){
      vars[i][j] = 0;
    }
  }

  while(loop){
    print_prompt();
    char *input = get_input();

    read_and_exec(input);
    free(input);
  }
  return 0;
}
