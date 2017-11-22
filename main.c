#include <stdlib.h>
#include <stdio.h>
#include <string.h>


int main( int argc, int *argv[] ){

  int loop = 1;
  while(loop){
    char input[100];
    fgets(input, sizeof(input), stdin);
    printf("You entered: %s", input);
  }
}
