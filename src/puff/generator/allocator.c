#include <puff/generator/allocator.h>

static Generator_t HEAP[GENERATOR_CAPACITY];

char alloc_gen(Generator_t**dest) {
    for(unsigned int i = 0; i < GENERATOR_CAPACITY; i++) {
        if(HEAP[i].rc == 0) { // free task
            Generator_t* gen = &HEAP[i];
            gen->rc++;
            *dest = gen;
            return 1;
        }
    }
    return 0;
}
