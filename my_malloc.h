#ifndef MY_MALLOC_H
#define MY_MALLOC_H

/*
 * to use sysmalloc or malloc replacements
 */

#define MALLOC(x)       malloc(x)
#define FREE(x)         free(x)
#define REALLOC(x,y)    realloc(x,y)
#define CALLOC(x,y)     calloc(x,y)

#endif
