/*
 *Required (use the function headers I provide, they may differ from the standard headers).
strlen [ int strlen( char * ) ]
strcpy/strncpy (choose one)  [ char * strcpy( char *dest, char *source )  char * strncpy( char *dest, char *source, int n)  ]
strcat/strncat (choose one)  [ char * strcat( char *dest, char *source )  char * strncat( char *dest, char *source, int n)  ]
strcmp  [ int strcmp( char *s1, char *s2 ) ]
strchr  [ char * strchr( char *s, char c ) ]
You must test every function you write, you will not get full credit for an untested functions
You do not need to write 7 functions, only 5, but you need to write 1 or the "n" versions. 
(So if you do strcpy then you have to do strncat)
A makefile that includes a run target. Do not automatically call run in the first target.
This will be explained in class on Tuesday
Extra
strstr [ char * strstr( char *s1, char * s2 ) ]
The other strn/str version of the functions you wrote above
When you test your functions,  run them alongside the regular ones so you can see if they behave the same way or not.
Remember you should call them something other than the regular names (like, mystrlen...). 
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "headers.h"

// Resets the 3 string to their original values
void reset( char *s0, char *s1, char *s2 ){
    //char s0[] = "?\n?W?";
    s0[0] = '?';
    s0[1] = '\n';
    s0[2] = '?';
    s0[3] = 'W';
    s0[4] = '?';
    s0[5] = 0;
    //char s1[] = "hello";
    s1[0] = 'h';
    s1[1] = 'e';
    s2[2] = s2[3] = 'l';
    s2[4] = 'o';
    s2[5] = 0;
    //char s2[] = "goodbye";
    s2[0] = 'g';
    s2[1] = s2[2] = 'o';
    s2[3] = 'd';
    s2[4] = 'b';
    s2[5] = 'y';
    s2[6] = 'e';
    s2[7] = 0;
    //printf("s0: %s\ns1: %s\ns2: %s\n", s0, s1, s2);
}

int my_strlen( char *str ){
    int i = 0;
    while( *str ){
        i++;
        str++;
    }
    return i;
}

char * my_strcpy( char *dest, char *source ){
    char *temp = dest;
    while( *dest = *source ){
        dest++;
        source++;
    }
    return temp;
}

char * my_strncat( char *dest, char *source, int n ){
    char *temp = dest;
    dest += strlen( dest );
    while( n-- ){
        *dest = *source;
        dest++;
        source++;
    }
    *dest = 0;
    return temp;
}

int main(){
    char s0[50] = "?\n?W?";
    char s1[50] = "hello";
    char s2[50] = "goodbye";
    printf("================\nTesting strlen(s1)\n");
    printf("standard: %ld\n", strlen(s1));
    reset( s0, s1, s2 );
    printf("mine: %d\n", my_strlen(s1));

    printf("================\nTesting strcpy(s0, s1):\n");
    printf("standard: %s\n", strcpy(s0, s1));
    reset( s0, s1, s2 );
    printf("mine: %s\n", my_strcpy(s0, s1) );

    printf("================\nTesting strncat(s2, s1, 4)\n");
    printf("standard: %s\n", strncat(s2, s1, 4));
    reset( s0, s1, s2 );
    printf("mine: %s\n", my_strncat(s2, s1, 4));
}

/*
s1: [?
?W?]
s2: [hello]
s3: [goodbye]

Testing strlen(s2):
[standard]: 5
[mine]: 5

Testing strcpy(s1, s2):
[standard]: [hello]
[mine]: [hello]

Testing strncpy(s1, s3, 3):
[standard]: [goolo]
[mine]: [goolo]

Testing strcat(s1, s3):
[standard]: [goologoodbye]
[mine]: [goologoodbye]

Testing strncat(s1, s2, 3):
[standard]: [goologoodbyehel]
[mine]: [goologoodbyehel]

Testing strchr(s1, 'l'):
[standard]: [0x7fff57d70a13]
[mine]: [0x7fff57d70a13]

Testing strchr(s1, 0):
[standard]: [0x7fff57d70a1f]
[mine]: [0x7fff57d70a1f]

Testing strchr(s1, 'z'):
[standard]: [0x0]
[mine]: [0x0]

Testing strcmp
 Comparting ab to abc:
 [standard]: [-99]
 [mine]: [-99]
 Comparting abc to ab:
 [standard]: [99]
 [mine]: [99]
 Comparting abc to abc:
 [standard]: [0]
 [mine]: [0]
 */
