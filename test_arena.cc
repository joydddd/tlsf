#include "arena.h"
#include <stdlib.h>

int main() { 
    tlsf::tlsf_internal::Arena arena; 
    size_t* pool1 = (size_t*)arena.Alloc();
    for (size_t i = 0; i < tlsf::tlsf_internal::PAGE_SIZE / sizeof(size_t);
         i++) {
        pool1[i] = i;
    }

    size_t* pool2 = (size_t*)arena.Alloc();
    for (size_t i = 0; i < tlsf::tlsf_internal::PAGE_SIZE / sizeof(size_t); i+=1245){
        pool2[i] = i;
    }


    /* check for correctness */
    for (size_t i = 0; i < tlsf::tlsf_internal::PAGE_SIZE / sizeof(size_t);
         i++) {
        if (pool1[i] != i) {
            exit(1);
        }
    }

    for (size_t i = 0; i < tlsf::tlsf_internal::PAGE_SIZE / sizeof(size_t);
         i += 1245) {
        if (pool2[i] != i) exit(1);
    }
}