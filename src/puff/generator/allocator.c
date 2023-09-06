#include <puff/generator/allocator.h>
#include <puff/cpu/cpu.h>

static Generator_t HEAP[_CPU_LEN][MAX_NUMBER_OF_GENERATORS_PER_CPU];

char alloc_gen(Generator_t**dest) {
    _CPU_ID_TYPE cpuid = getcpu();
    for(unsigned int i = 0; i < MAX_NUMBER_OF_GENERATORS_PER_CPU; i++) {
        if(HEAP[cpuid][i].rc == 0) { // free task
            Generator_t* gen = &HEAP[cpuid][i];
            gen->rc++;
            *dest = gen;
            return 1;
        }
    }
    return 0;
}
