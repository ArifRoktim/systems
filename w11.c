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

void strip_newline( char *str ){
  while( *str ){
    if( *str == '\n' ){
      *str = 0;
    }
    str++;
  }
}

// returns new string
char * strip_spaces( char *str ){
  int size = strlen(str);
  char *ret = (char *) calloc(1, size);
  char tmp[size];
  int i = 0;
  for(; i < size; i++){
    tmp[i] = 0;
  }
  i = 0;
  int j = 0;
  // first remove consecutive spaces
  while( i + j < size ){
    if(str[i+j] == ' ' && (i+j+1 < size) && str[i+j+1] == ' '){
      tmp[i] = ' ';
      i++;
      while(str[i+j] == ' '){
        j++;
      }
    } else {
      tmp[i] = str[i + j];
      i++;
    }
  }
  // then remove spaces around semicolons
  i = j = 0;
  while( i + j < size ){
    if(tmp[i+j] == ' ' && (i+j+1 < size) && tmp[i+j+1] == ';'){
      ret[i] = ';';
      i++;
      j++;
    } else if(tmp[i+j] == ' ' && (i+j-1 >= 0) && tmp[i+j-1] == ';'){
      j++;
    } else {
      ret[i] = tmp[i + j];
      i++;
    }
  }
  return ret;
}
