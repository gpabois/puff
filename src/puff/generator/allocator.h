#ifndef __GEN_ALLOCATOR_H__
#define __GEN_ALLOCATOR_H__

#include <puff/generator/generator.h>

// Max number of generators.
#define MAX_NUMBER_OF_GENERATORS_PER_CPU 512

/* Alloc a generator. 
* Returns 0 if failed. 
*/
char alloc_gen(Generator_t**dest);

#endif