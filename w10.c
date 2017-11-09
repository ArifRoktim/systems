#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

void errorhandler( int no ){
  if( no ){
    strerror(no);
    exit(1);
  }
}

static void sighandler(int signo){
  //printf("signo:%d\n",signo);
  if( signo == SIGINT ){
    errno = 0;
    int fd = open("errorlog", O_CREAT | O_APPEND | O_WRONLY, 0644);
    errorhandler(errno);
    char *msg = "Program exited due to SIGINT\n";
    errno = 0;
    write( fd, msg, strlen(msg) * sizeof(char) );
    errorhandler(errno);
    close(fd);
    // Exit code from:
    // http://tldp.org/LDP/abs/html/exitcodes.html
    exit(128 + SIGINT);
  }
  if( signo == SIGUSR1 ){
    printf("Parent's pid is: %d\n", getppid());
  }
}
int main(){
  signal( SIGINT, sighandler );
  signal( SIGUSR1, sighandler );
  while(1){
    printf("My process id: %d\n", getpid());
    sleep(1);
  }
}
