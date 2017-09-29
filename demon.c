#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* FROM $ man 3 strcpy:
SYNOPSIS
   #include <string.h>

   char *strcpy(char *dest, const char *src);

   char *strncpy(char *dest, const char *src, size_t n);

DESCRIPTION
   The  strcpy()  function copies the string pointed to by src, including the
   terminating null byte ('\0'), to the  buffer  pointed  to  by  dest.   The
   strings  may  not  overlap,  and the destination string dest must be large
   enough to receive the copy.  Beware of buffer overruns!  (See BUGS.)

   The strncpy() function is similar, except that at most n bytes of src  are
   copied.  Warning: If there is no null byte among the first n bytes of src,
   the string placed in dest will not be null-terminated.

   If the length of src is less than  n,  strncpy()  writes  additional  null
   bytes to dest to ensure that a total of n bytes are written.
*/

int main(){
    char str0[] = "Hello world!";
    char str1[50];
    printf("[%s] is %p\n", str0, &str0 );
    printf("[%s] is %p\n", str1, &str1 );
    printf("strcpy( str1, str0 );\n");
    strcpy( str1, str0 );
    printf("[%s] is %p\n", str0, &str0 );
    printf("[%s] is %p\n", str1, &str1 );
    printf("strncpy( str1, str0, 5);\n");
    char str2[50];
    strncpy(str2, str0, 5);
    printf("[%s] is %p\n", str0, &str0 );
    printf("[%s] is %p\n", str2, &str2 ); // no null terminator!
    printf("strncpy(str3, str0, 10);\n");
    char str3[50] = {0};
    strncpy(str3, str0, 10);
    printf("[%s] is %p\n", str0, &str0 );
    printf("[%s] is %p\n", str3, &str3 );
}
