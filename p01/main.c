#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include "parse.h"
#include "builtin.h"
#include "misc.h"

int loop = 1;
char *vars[256][2];

void rainbow(){
  mkfifo("/tmp/shell", 0600);
  int f = fork();
  if(f){
    int file = open("/tmp/shell", O_RDONLY);
    while(loop){
      int f1 = fork();
      if(f1){
        wait(0);
      } else {
        dup2(file, STDIN_FILENO);
        execlp("lolcat", "lolcat");
      }
    }
  } else {
    int file = open("/tmp/shell", O_WRONLY);
    dup2(file, STDOUT_FILENO);
  }

}

int main( int argc, char *argv[] ){
  
  
  int i = 1;
  int bool_rainbow = 0;
  for(; i < argc; i++){
    if( !strcmp(argv[i], "-l") ){
      bool_rainbow = 1;
    }
  }

  if(bool_rainbow){
    rainbow();
  }
  
  // Run initialization stuff
  init();

	while(loop){
		print_prompt();
		char *input = get_input();

		if( input ){
			read_and_exec(input);
			free(input);
		}
	}

	// free stuff (and later save history)
	cleanup();

	return 0;
}
