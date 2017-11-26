#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include "builtin.h"
#include "parse.h"

void cd(char *dir){
  int status = chdir(dir);
  if(status){
    printf("shell: cd: %s: %s\n", dir, strerror(errno));
  }
}

// Do pre-exit stuff here
void safely_exit(){
  // TO BE IMPLEMENTED LATER
  exit(0);
}


void print_prompt(){
  // Get user's cwd
  char cwd[256];
  getcwd(cwd, sizeof(cwd));
  // Replace the home directory path with '~'

  
  printf("%s $ ", cwd);
}

char * get_input(){
  char raw_input[100];
  if( fgets(raw_input, sizeof(raw_input), stdin) == NULL ){
    safely_exit();
  }
  strip_newline(raw_input);
  char *input = strip_spaces(raw_input);
  //printf("Raw: %s\nInput: %s\n", raw_input, input);
  //printf("Input 0: %s\n", input);
  return input;
}
