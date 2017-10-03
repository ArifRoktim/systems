#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "my_string.h"

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
