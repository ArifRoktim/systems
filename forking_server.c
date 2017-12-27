#include "pipe_networking.h"
#include <signal.h>

void process(char *s);
void error_handler(int status);
void subserver(int from_client);

static void sighandler(int signo) {
  if (signo == SIGINT) {
    remove(KNOWN_PIPE);
    exit(0);
  }
}

int main() {
  signal(SIGINT, sighandler);
  int from_client;
  int loop = 1;
  while(loop){
    from_client = server_setup();
    int f = fork();
    if(f){
      close(from_client);
    } else {
      subserver(from_client);
      exit(0);
    }
  }
  return 0;
}

void subserver(int from_client) {
  printf("[Subserver] Connect to client\n");
  int to_client = server_connect(from_client);
  printf("[Subserver] Read data from client\n");
  char buf[BUFFER_SIZE];
  while( read(from_client, buf, sizeof(buf)) ){
    printf("[Subserver] Proceessing data: [%s]\n", buf);
    process(buf);
    printf("[Subserver] Write processed data to client: [%s]\n", buf);
    error_handler( write(to_client, buf, sizeof(buf)) );
  }
}

void process(char * s) {
  while(*s){
    if(*s == ' ')
      *s = '_';
    s++;
  }
}
