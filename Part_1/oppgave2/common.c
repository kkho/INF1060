#include "common.h"

/**
 * homemade allocation of memory, this should work for instead of malloc,
 * and this gives more neat allocation and don't need to screw up with
 * malloc and free and valgrind bugs, note, to use this, I recommend using static
 * array with a given size. 
 * @param size
 * @return allocated data.
 */

void *stack_malloc(size_t size) {
    void *p = &malloc_data[malloc_used];
    if(size + malloc_used > MAX_SIZE) return 0;  /* out of memory */
    malloc_used += size;
    return p;
}