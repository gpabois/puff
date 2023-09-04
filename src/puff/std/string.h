#ifndef __STRING_H__
#define __STRING_H__

void memcpy(void * destination, const void * source, unsigned int size )
{
    for(unsigned int i = 0; i < size; i++) {
        char* dest_byte = (char*)(destination + i);
        const char* src_byte = (const char*)(source + i);
        *dest_byte = *src_byte;
    }
}

#endif