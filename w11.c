#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char ** parse_args( char * line ){
  char **args = malloc( 5 * sizeof(char *));
  int n = 0;
  while( line ){
    char * arg = strsep( &line, " ");
    args[n] = arg;
    n++;
  }
  return args;
}

int main(){

  /*
  char line[100] = "wow-this-is-cool";
  char *s1 = line;
  printf("[%s]\n", strsep( &s1, "-" ));
  printf("[%s]\n", strsep( &s1, "-" ));
  printf("[%s]\n", strsep( &s1, "-" ));
  printf("[%s]\n", strsep( &s1, "-" ));
  printf("[%s]\n", strsep( &s1, "-" ));
  printf("[%s]\n", s1);
  */
  char line[100] = "ls -a -l";
  char **args = parse_args(line);
  execvp( args[0], args);

  return 0;

}
