#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char ** parse_args( char * line ){
  int size = 5;
  char **args = malloc( size * sizeof(char *));
  int n = 0;
  while( line ){
    if( n + 1 > size ){
      size += 5;
      args = realloc( args, size * sizeof(char *));
    }
    args[n] = strsep( &line, " ");
    n++;
  }
  args[n+1] = 0;
  return args;
}

void print_str_arr( char **arr ){
  char *str = *arr;
  int n = 0;
  while( str ){
    n++;
    printf("%d:\t%s\n", n-1, str );
    str = *(arr + n);
  }
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

  char line[100] = "ls -a -l -F -h -i .";
  char **args = parse_args(line);

  printf("Printing **args...\n");
  print_str_arr( args );

  printf("Running execvp( args[0], args )\n");
  execvp( args[0], args );

  return 0;

}
