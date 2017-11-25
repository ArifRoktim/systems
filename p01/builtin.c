#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

void cd(char *dir){
  int status = chdir(dir);
  if(status){
    printf("shell: cd: %s: %s\n", dir, strerror(errno));
  }
}
