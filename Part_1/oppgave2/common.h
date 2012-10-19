#ifndef COMMON_H
#define COMMON_H
#define MAX_SIZE 100000
#include <stdio.h>
#include <stdlib.h>

/*homemade trick for allocating memory without malloc tricks*/
unsigned char malloc_data[MAX_SIZE];
size_t malloc_used;  /* automatically initialized to zero */

void *stack_malloc(size_t size);



#endif

