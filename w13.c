#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

void error(int status){
  if(status == -1){
    strerror(errno);
    exit(1);
  }
}

int main(){
  int ctp[2];
  int ptc[2];
  pipe(ctp);
  pipe(ptc);
  int READ = 0;
  int WRITE = 1;

  int f = fork();
  if(f){
    // Parent case
    // Send data to child
    int data = 1337;
    printf("[Parent] Sending \"%d\" to child\n", data);
    write(ptc[READ], &data, sizeof(data));
    // Wait for child to send data back
    int status;
    wait(&status);
  } else {
    // Child case
    // Read data
    int data;
    read(ptc[WRITE], &data, sizeof(data));
    printf("[Child] Got data: %d\n", data);
  }

}
