#ifndef __GEN_ALLOCATOR_H__
#define __GEN_ALLOCATOR_H__

#include <puff/generator/generator.h>

// Max number of generators.
#define GENERATOR_CAPACITY 512

/* Alloc a generator. 
* Returns 0 if failed. 
*/
char alloc_gen(Generator_t**dest);

#endif