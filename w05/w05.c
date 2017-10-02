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

int my_strlen( char *str ){
    int i = 0;
    while( *str ){
        i++;
        str++;
    }
    return i;
}

int main(){
    char s1[] = "?\n?W?";
    char s2[] = "hello";
    char s3[] = "goodbye";

    printf("Testing strlen(s2)\n");
    printf("standard: %d\nmine: %d\n", strlen(s2), my_strlen(s2) );
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
