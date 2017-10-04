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

#include "my_string.h"

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
    dest += my_strlen( dest );
    while( n-- ){
        *dest = *source;
        dest++;
        source++;
    }
    *dest = 0;
    return temp;
}

char * my_strchr( char *s, char c ){
    while( *s && *s != c ){
        s++;
    }
    if( *s == c ){
        return s;
    } else {
        return 0;
    }
}
