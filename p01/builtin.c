#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int fork_and_exec( char *program, char **args ){
  int f = fork();
  if(f){
    //Parent case
  } else {
    execvp( program, args );;
  }
}
