#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int ret_size( char *name ){
    struct stat sb;
    stat( name, &sb );
    return sb.st_size;
}

int main(){

    DIR *dir = opendir(".");

    struct dirent *dirent;
    printf("Printing out all files in directory...\n");
    printf("Dir?\tSize\tName\n");
    unsigned long total = 0;
    while( dirent = readdir(dir) ){
        // print whether is directory or not
        if( dirent->d_type == DT_DIR ){
            printf("d\t");
        } else {
            printf("-\t");
        }
        // print file size
        long size = 0;
        total += (size = ret_size( dirent->d_name ));
        printf("%d\t", size);
        // print file name
        printf("%s\n", dirent->d_name );
        // print total file size
    }
    printf("total %ld\n", total);


    closedir(dir);
    return 0;
}
