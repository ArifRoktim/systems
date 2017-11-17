#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>

int main(){
  printf("Pre fork!\n");

  int f = fork();
  int f1 = 0;
  int status;

  if(f){
    int f1 = fork();
    if( f1 ){
      int pid = wait(&status);
      printf("Child with pid %d slept for %d seconds\n", pid, WEXITSTATUS(status));
      printf("Parent done.\n");
      exit(0);
    }
  }
  if( f == 0 || f1 == 0 ){
    // Child process
    printf("I'm a child! My pid is: %d\n", getpid());
    srand(time(NULL) + getpid());
    int randint = rand() % 16 + 5; // return rand int in range [5,20]
    //printf("Sleeping for %d seconds.\n",randint);
    sleep(randint);
    return randint;
  }
}
