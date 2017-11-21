#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

void error(int status){
  if(status == -1){
    strerror(errno);
  }
  exit(1);
}

int main(){
  int child_to_parent[2];
  int parent_to_child[2];
  error( pipe(child_to_parent) );
  error( pipe(parent_to_child) );

  int f = fork();
  if(f){
    // Parent case
    int READ = child_to_parent[0];
    int WRITE = parent_to_child[0];
    // Send data to child
    int data = 1337;
    printf("[Parent] Sending \"%d\" to child\n", data);
    error( write(WRITE, &data, sizeof(data)) );
    // Wait for child to send data back
    int status;
    wait(&status);
  } else {
    // Child case
    int READ = parent_to_child[1];
    int WRITE = child_to_parent[1];
    // Read data
    int data;
    error( read(READ, &data, sizeof(data)) );
    printf("[Child] Got data: %d\n", data);
  }

}
