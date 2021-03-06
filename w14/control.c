#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#define KEY 0x1337
#define NONE -1
#define CREATE 0
#define VIEW 1
#define REMOVE 2

int create_sem(){
  int status = semget(KEY, 1, IPC_CREAT | IPC_EXCL | 0600);
  if(status == -1){
    if(errno == EEXIST){
      printf("Semaphore already exists\n");
    } else {
      printf("%s\n", strerror(errno));
    }
  } else {
    printf("Semaphore created: %d\n", status);
  }
  return status;
}

int get_sem(){
  int status = semget(KEY, 1, 0600);
  if(status == -1){
    printf("%s\n", strerror(errno));
  }
  return status;
}

int set_sem(int value){
  int desc = get_sem();
  int status = semctl(desc, 0, SETVAL, value);
  if( status == -1 ){
    printf("%s\n", strerror(errno));
  } else {
    printf("Value set: %d\n", value);
  }
  return status;
}

int view_sem(){
  int desc = get_sem();
  //printf("desc: %d\n", desc);
  int val = -1;
  if(desc == -1){
  } else {
    val = semctl( desc, 0, GETVAL );
  }
  return val;

}

int remove_sem(){
  int desc = get_sem();
  int status = semctl(desc, 0, IPC_RMID);
  if(status == -1){
    printf("%s\n", strerror(errno));
  } else {
    printf("Removed semaphore\n");
  }
  return status;
}

int main( int argc, char *argv[] ){
  // First parse command line args
  int i = 0;
  int mode = NONE;
  for(; i < argc; i++){
    if( !strcmp(argv[i], "-c") && argc == 3 ){
      mode = CREATE;
    }
    if( !strcmp(argv[i], "-v") ){
      mode = VIEW;
    }
    if( !strcmp(argv[i], "-r") ){
      mode = REMOVE;
    }
  }
  //printf("%d\n", mode);

  // Do stuff based on mode
  if( mode == NONE ){
    printf("Invalid syntax\n");
    exit(1);
  }
  if( mode == CREATE ){
    //printf("%s\n", argv[2]);
    int number = (int) strtol(argv[2], NULL, 10);
    if(create_sem() != -1)
      set_sem(number);
  }
  if( mode == VIEW ){
    printf("%d\n", view_sem());
  }
  if( mode == REMOVE ){
    remove_sem();
  }
  
  return 0;
}
