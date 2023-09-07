#include <puff/generator/allocator.h>
#include <puff/cpu/cpu.h>

/**
 * @brief The memory containing the allocated generators.
 * 
 * Each CPU has its own memory area.
 */
static Generator_t __gens[_CPU_LEN][MAX_NUMBER_OF_GENERATORS_PER_CPU];

char alloc_gen(Generator_t**dest) {
    _CPU_ID_TYPE cpuid = getcpu();
    for(unsigned int i = 0; i < MAX_NUMBER_OF_GENERATORS_PER_CPU; i++) {
        if(__gens[cpuid][i].rc == 0) { // free task
            Generator_t* gen = &__gens[cpuid][i];
            *dest = gen;
            return 1;
        }
    }
    return 0;
}
