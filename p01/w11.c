#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char ** parse_args( char * line, char delim ){
  int size = 5;
  char **args = malloc( size * sizeof(char *));
  int n = 0;
  while( line ){
    if( n + 1 > size || n == size ){
      size += 5;
      args = realloc( args, size * sizeof(char *));
    }
    args[n] = strsep( &line, &delim);
    n++;
  }
  args[n] = 0;
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

