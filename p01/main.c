#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "parse.h"

char * print_prompt(){
  char cwd[256];
  getcwd(cwd, sizeof(cwd));
  printf("%s $ ", cwd);
}

int main( int argc, char *argv[] ){

  int main_loop = 1;
  while(main_loop){
    print_prompt();
    char raw_input[100];
    fgets(raw_input, sizeof(raw_input), stdin);
    strip_newline(raw_input);
    char *input = strip_spaces(raw_input);
    //printf("Raw: %s\nInput: %s\n", raw_input, input);

    read_and_exec(input);
    free(input);
  }
  return 0;
}
