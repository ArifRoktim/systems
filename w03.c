#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int main(){
    srand( time(NULL) ); //seed random number generator
    int ar[10];
    int i;
    // populate array with random values
    for( i = 0; i < 10; i++ ){
        if( i == 9 ){
            ar[i] = 0;
        } else {
            ar[i] = rand();
        }
        printf("ar[%d] is %d\n", i, ar[i]);
    }
    // populate array with values of ar in reverse order
    int ar2[10];
    int *one = &ar2[0];
    int *two = &ar[9];
    for( i = 0; i < 10; i++ ){
        *one = *two;
        *one++;
        *two--;
    }
    // print out second array
    for( i = 0; i < 10; i++ ){
        printf("ar2[%d] is %d\n", i, ar2[i] );
    }
}
