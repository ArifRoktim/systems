#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

int rand_int(){
    int fd = open( "/dev/random", O_RDONLY );
    if( fd ){
        int rand;
        read( fd, &rand, sizeof(int) );
        return rand;
    } else {
        printf("You done messed up. /dev/random doesn't exist. Returning 0.");
        return 0;
    }
}

int main(){
    int i;
    // Populate array with rand ints
    printf("Populate array with rand ints\n");
    int arr[10];
    for( i = 0; i < 10; i++ ){
        arr[i] = rand_int();
    }
    // Print array
    printf("Print array\n");
    for( i = 0; i < 10; i++){
        printf("Arr[%d]: %d\n", i, arr[i]);
    }
    // Write array to file
    printf("Write array to file\n");
    int fd = open( "randints", O_WRONLY | O_CREAT | O_TRUNC, 0644 );
    if( fd ){
        write( fd, arr, sizeof(arr) );
    } else {
        strerror(errno);
    }
    close( fd );
    // Read from file
    printf("Read from file\n");
    fd = open( "randints", O_RDONLY, 0 );
        int arr1[10];
    if( fd ){
        read( fd, arr1, sizeof(arr1));
        for( i = 0; i < 10; i++ ){
            printf("Arr1[%d]: %d\n", i, arr1[i]);
        }
    } else {
        strerror(errno);
    }
    return 0;
}

/*
A main function that:
 
Sample output:
Generating random numbers:
        random 0: 198116400
        random 1: 2592608753
        random 2: 2833624368
        random 3: 3273750590
        random 4: 3548697368
        random 5: 3876828898
        random 6: 2617393183
        random 7: 1720936907
        random 8: 682596330
        random 9: 2411695830

Writing numbers to file...

Reading numbers from file...

Verification that written values were the same:
        random 0: 198116400
        random 1: 2592608753
        random 2: 2833624368
        random 3: 3273750590
        random 4: 3548697368
        random 5: 3876828898
        random 6: 2617393183
        random 7: 1720936907
        random 8: 682596330
        random 9: 2411695830
 */
