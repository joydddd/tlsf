#include <cstdlib>

#include "tlsf.h"
#define PAGE_SIZE 4096 // 4KB

int main() {
    void* mem = malloc(PAGE_SIZE);
    void* mem1 = malloc(PAGE_SIZE);
    void* mem2 = malloc(PAGE_SIZE);
    tlsf_t tlsf = tlsf_create(mem);
    pool_t pool1 = tlsf_add_pool(tlsf, mem1, PAGE_SIZE);
    pool_t pool2 = tlsf_add_pool(tlsf, mem2, PAGE_SIZE);

    void* array1 = tlsf_malloc(tlsf, 100*sizeof(int));
    for (int i = 0; i < 100;i++){
        ((int*)array1)[i] = i;
    }
    void* array2 = tlsf_malloc(tlsf, 10 * sizeof(int));
    for (int i = 0; i < 10; i++) {
        ((int*)array2)[i] = i;
    }

    for (int i = 0; i < 100; i++) {
        if (((int*)array1)[i] != i) exit(1);
    }

    for (int i = 0; i < 10; i++) {
        if (((int*)array2)[i] != i) exit(1);
    }
}