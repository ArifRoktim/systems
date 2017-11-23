#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int fork_and_exec( char *program, char **args ){
  int f = fork();
  if(f){
    int status;
    wait(&status);
  } else {
    execvp( program, args );;
  }
}
