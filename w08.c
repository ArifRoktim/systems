#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>
#include <fcntl.h>

void print_size( struct stat *sb ){
    printf("Size of file: %ld\n", sb->st_size );
}

void print_mode( struct stat *sb ){
    int mode = sb->st_mode;
    mode = mode >> 9;
    printf("%d\n", mode );
}

int main(){
    struct stat sb;
    stat("w08.c", &sb);
    printf("===========Info for file \"w08.c\"===========\n");
    print_size( &sb );
    print_mode( &sb );

    return 0;
}
