#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include "parse.h"

extern int loop;
extern char *vars[256][2];

void init(){
	// Blank out variables array
	int i = 0;
	int j = 0;
	for(; i < 256; i++){
		for(; j < 2; j++){
			vars[i][j] = 0;
		}
	}

	// Execute contents of init file
	int f = open(".shellrc", O_RDONLY, 0);
	char file[1024];
	for( i = 0; i < 1024; i++ ){
		file[i] = 0;
	}
	if( f ){
		int status = read(f, file, sizeof(file));
		if(status == -1){
			//printf("Error reading init file: %s", strerror(errno));
			return;
		}

		char *delim = "\n";
		char **lines = parse_args(file, delim);
		char *line = *lines;
		i = 0;
		while( line ){
			read_and_exec(line);
			i++;
			line = lines[i];
		}
		free(lines);
	} else {
		printf("Error opening init file: %s", strerror(errno));
	}
}

void cleanup(){
	// Free variables array
	int i = 0;
	while( i < 256 && vars[i][0] ){
		free(vars[i][0]);
		free(vars[i][1]);
		i++;
	}
}

void rainbow(){
  mkfifo("/tmp/shell", 0600);
  int f = fork();
  if(f){
    int file = open("/tmp/shell", O_RDONLY);
    while(loop){
      int f1 = fork();
      if(f1){
        int status;
        wait(&status);
      } else {
        dup2(file, STDIN_FILENO);
		char *args[] = {"lolcat", 0};
        execvp("lolcat", args);
		printf("Error execing lolcat: %s\n", strerror(errno));
      }
    }
  } else {
    int file = open("/tmp/shell", O_WRONLY);
    dup2(file, STDOUT_FILENO);
  }
}

