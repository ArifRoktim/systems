#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>

int main(){
  printf("Pre fork!\n");

  int f = fork();
  int status;

  if(f){
    int f1 = fork();
    if(f1){
      int pid = wait(&status);
      printf("Child with pid %d slept for %d seconds\n", pid, WEXITSTATUS(status));
      printf("Parent done.\n");
      exit(0);
    }
    if( f1 == 0 ){
      printf("I'm a child! My pid is: %d\n", getpid());
      srand(time(NULL));
      int randint = rand() % 16 + 5; // return rand int in range [5,20]
      sleep(randint);
      //printf("Slept for %d seconds.\n",randint);
      return randint;
    }
  } 
  if( f == 0 ){
    // Child process
    printf("I'm a child! My pid is: %d\n", getpid());
    srand(time(NULL));
    int randint = rand() % 16 + 5; // return rand int in range [5,20]
    sleep(randint);
    //printf("Slept for %d seconds.\n",randint);
    return randint;
  }
}
