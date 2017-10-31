#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>
#include <fcntl.h>

void print_size( struct stat *sb ){
    printf("Size: %ld\n", sb->st_size );
}

void print_ls( int perm ){
  if( perm == 7 ){
    printf("rwx");
  } else if( perm == 6 ){
    printf("rw-");
  } else if( perm == 5 ){
    printf("r-x");
  } else if( perm == 4 ){
    printf("r--");
  } else if( perm == 3 ){
    printf("-wx");
  } else if( perm == 2 ){
    printf("-w-");
  } else if( perm == 1 ){
    printf("--x");
  }
}

void print_mode( struct stat *sb ){
    unsigned int mode = sb->st_mode;
    printf("Mode: %o\n", mode);
    int others = mode % 8;
    mode /= 8;
    int group = mode % 8;
    mode /= 8;
    int owner = mode % 8;
    printf("Owner: %d, Group: %d, Other: %d\n", owner, group, others);
    print_ls(owner);
    print_ls(group);
    print_ls(others);
    printf("\n");
}

void print_time( struct stat *sb ){
    printf("Time accessed: %s\n", ctime( &(sb->st_atime) ));
}

int main(){
    struct stat sb;
    stat("w08.c", &sb);
    printf("===========Info for file \"w08.c\"===========\n");
    print_size( &sb );
    print_mode( &sb );
    print_time( &sb );
    return 0;
}
