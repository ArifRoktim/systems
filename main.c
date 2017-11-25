#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "parse.h"

int main( int argc, char *argv[] ){

  int loop = 1;
  while(loop){
    char raw_input[100];
    printf("$ ");
    fgets(raw_input, sizeof(raw_input), stdin);
    strip_newline(raw_input);
    char *input = strip_spaces(raw_input);
    //printf("Raw: %s\nInput: %s\n", raw_input, input);

    read_and_exec(input);
    free(input);
  }
}
