#ifndef __GEN_ALLOCATOR_H__
#define __GEN_ALLOCATOR_H__

#include <puff/generator/generator.h>

/**
* @brief Max number of generators per cpu
*/
#define MAX_NUMBER_OF_GENERATORS_PER_CPU 512

/**
 * @brief Allocate a new generator
 * 
 * @note
 * Each CPU has its own memory area.
 * 
 * @param dest the receiver of the allocated generator's pointer.
 * @return 1 on succcess, 0 on failure
 */
char alloc_gen(Generator_t**dest);

#endif